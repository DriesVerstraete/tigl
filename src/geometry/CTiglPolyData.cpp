/*
* Copyright (C) 2007-2013 German Aerospace Center (DLR/SC)
*
* Created: 2013-02-09 Martin Siggel <Martin.Siggel@dlr.de>
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* @file CTiglPolyData.cpp
* @brief Handles polygon data for export and rendering usage
*/

#include "CTiglPolyData.h"
#include "CTiglPoint.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "tigl.h"
#include "tixi.h"

#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <set>
#include <utility>

#include <fstream>
#include <cfloat>
#include <cstdio>

using namespace tigl;

#ifdef _MSC_VER
    #define snprintf _snprintf
#endif


#define COMP_TOLERANCE 1.e-10


struct TiglPointComparer;

class PointImpl 
{
public:
    PointImpl() : 
        p_(CTiglPoint(0,0,0)),
        n_(CTiglPoint(1,0,0)) 
    {
    }

    PointImpl(const CTiglPoint& p, const CTiglPoint& n) : p_(p), n_(n) 
    {
        realDataMap.clear();
    }

    CTiglPoint& point(){ return p_; }
    CTiglPoint& normal(){ return n_; }

    const CTiglPoint& getPoint() const { return p_; }
    const CTiglPoint& getNormal()const { return n_; }
    
    void setRealData(const char * txt, double value)
    {
        realDataMap[txt] = value;
    }
    
    double getRealData(const char * txt) const 
    {
        std::map<std::string, double>::const_iterator it=realDataMap.find(txt);
        if (it != realDataMap.end()) {
            return it->second;
        }
        else {
            return UNDEFINED_REAL;
        }
    }

private:
    CTiglPoint p_;
    CTiglPoint n_;
    
    std::map<std::string, double> realDataMap;
};

typedef std::map<PointImpl, unsigned int, TiglPointComparer> PointMap;

// Comparer for gp_Pnts
struct TiglPointComparer
{
    bool isSmaller(const CTiglPoint& lhs, const CTiglPoint& rhs) const 
    {
        // if two points lie inside the epsilon environment
        // they should be the same, hence lhs is not smaller than rhs
        if (lhs.distance2(rhs) < COMP_TOLERANCE ) {
            return false;
        }


        // as lhs and rhs don't lie inside an epsilon environment
        if (lhs.x < rhs.x) {
            return true;
        }
        else if (lhs.x == rhs.x) {
            if (lhs.y < rhs.y) {
                return true;
            }
            else if (lhs.y == rhs.y) {
                return lhs.z < rhs.z;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }


    // function should only return true, if lhs < rhs
    bool operator()(const PointImpl& lhs, const PointImpl& rhs) const
    {
        const CTiglPoint& leftP  = lhs.getPoint();
        const CTiglPoint& rightP = rhs.getPoint();

        const CTiglPoint& leftN  = lhs.getNormal();
        const CTiglPoint& rightN = rhs.getNormal();

        if (isSmaller(leftP,rightP)) {
            return true;
        }
        else {
            // if points are equal, compare normals
            if (leftP.distance2(rightP) <  COMP_TOLERANCE ) {
                return isSmaller(leftN, rightN);
            }
            else {
                return false;
            }
        }
    }
};


//class to store a polygon by its point indices
struct PolyIndexList
{
    PolyIndexList(int num) : _metadata("")
    {
        myid = num;
    }

    void setMetadata(const std::string& str)
    {
        _metadata = str;
    }

    const std::string& getMetadata() const
    {
        return _metadata;
    }
    
    void addPoint(int index);
    
    void repair();
    
    void setRealData(const char * txt, double value)
    {
        realDataMap[txt] = value;
    }
    
    double getRealData(const char * txt) const 
    {
        std::map<std::string, double>::const_iterator it=realDataMap.find(txt);
        if (it != realDataMap.end()) {
            return it->second;
        }
        else {
            return UNDEFINED_REAL;
        }
    }
    
    int getNVert() const { return pindex.size();}
    int getPointIndex(int i) const { return pindex.at(i); }
    
private:
    std::vector<int> pindex;

    //each polygon should have it's own metadata
    std::string _metadata;
    
    std::map<std::string, double> realDataMap;

    int myid;
};


class ObjectImpl 
{
public:
    ObjectImpl()
    {
        pointlist.clear();
        polys.clear();
        pPoints.clear();
        has_normals = false;
        has_metadata = false;
        metaDataElements = "";
    }

    void addPointNorm(const CTiglPoint &p, const CTiglPoint& norm, long polynum);
    unsigned long addPointNorm(const CTiglPoint &p, const CTiglPoint &norm);
    
    unsigned long addTriangleByVertexIndex(unsigned long i1, unsigned long i2, unsigned long i3 );
    
    void addPolygon(const CTiglPolygon&);
    
    unsigned long getNPolygons() const;
    unsigned long getNPointsOfPolygon(unsigned long ipoly) const;

    const CTiglPoint& getVertexPoint(unsigned long iVertexIndex) const;
    const CTiglPoint& getVertexNormal(unsigned long iVertexIndex) const;

    unsigned long getVertexIndexOfPolygon(unsigned long ipoint, unsigned long ipoly) const;

    bool has_normals;
    bool has_metadata;

    // we use this container to store point data, it allows us to find
    // efficiently a specific point in the list
    PointMap pointlist;

    // this vector keeps track of the order of points, it complies with
    // the polygon indices
    std::vector<PointImpl*> pPoints;

    std::vector<PolyIndexList> polys;
    
    std::set<std::string> polyDataElems;
    std::set<std::string> vertexDataElems;
    
    std::string metaDataElements;
};



// -----------------------------------------------------------------------//

CTiglPolyData::CTiglPolyData()
{
    _objects.clear();
    // we want to have one object by default
    _objects.push_back(new CTiglPolyObject());
    itCurrentObj = _objects.begin();
}

CTiglPolyData::~CTiglPolyData()
{
    std::vector<CTiglPolyObject*>::iterator pObj_it = _objects.begin();
    for (; pObj_it != _objects.end(); ++pObj_it) {
        delete *pObj_it;
    }
}

CTiglPolyObject& CTiglPolyData::currentObject()
{
    return **itCurrentObj;
}

CTiglPolyObject& CTiglPolyData::createNewObject() 
{
    _objects.push_back(new CTiglPolyObject());

    itCurrentObj = _objects.end()-1;
    return currentObject();
}

// changes the current surface, we count from 1 to getNSurfaces
CTiglPolyObject& CTiglPolyData::switchObject(unsigned int iObject)
{
    if (iObject >= 1 && iObject <= _objects.size()) {
        itCurrentObj = _objects.begin() + iObject -1;
        return currentObject();
    }
    else {
        throw tigl::CTiglError("Invalid surface index in CTiglPolyData::switchObject!", TIGL_INDEX_ERROR);
    }
}

unsigned int CTiglPolyData::getNObjects()
{
    return _objects.size();
}

unsigned long CTiglPolyData::getTotalPolygonCount()
{
    std::vector<CTiglPolyObject*>::iterator co = itCurrentObj;

    unsigned long nPolys = 0;

    for (unsigned int i = 1; i <= getNObjects(); ++i) {
        CTiglPolyObject& obj = switchObject(i);
        nPolys += obj.getNPolygons();
    }

    itCurrentObj = co;
    return nPolys;
}

unsigned long CTiglPolyData::getTotalVertexCount()
{
    std::vector<CTiglPolyObject*>::iterator co = itCurrentObj;

    unsigned long nVertices = 0;

    for (unsigned int i = 1; i <= getNObjects(); ++i) {
        CTiglPolyObject& obj = switchObject(i);
        nVertices += obj.getNVertices();
    }

    itCurrentObj = co;
    return nVertices;
}

void CTiglPolyData::writeVTK(const char *filename)
{
    TixiDocumentHandle handle;
    createVTK(handle);
    if (tixiSaveDocument(handle, filename)!= SUCCESS) {
        throw CTiglError("Error saving vtk file!");
    }
    LOG(INFO) << "VTK Export succeeded with " << getTotalPolygonCount()
              << " polygons and " << getTotalVertexCount() << " vertices." << std::endl;
}

void CTiglPolyData::createVTK(TixiDocumentHandle& handle)
{
    tixiCreateDocument("VTKFile", &handle);
    tixiAddTextAttribute(handle, "/VTKFile", "type", "PolyData");
    tixiAddTextAttribute(handle, "/VTKFile", "version", "0.1");
    tixiAddTextAttribute(handle, "/VTKFile", "byte_order", "LittleEndian");
    tixiAddTextAttribute(handle, "/VTKFile", "compressor", "vtkZLibDataCompressor");

    std::stringstream stream;
    stream << "tigl " << tiglGetVersion();
    tixiCreateElement(handle, "/VTKFile","MetaData");
    tixiAddTextAttribute(handle, "/VTKFile/MetaData", "creator", stream.str().c_str());
    
    tixiCreateElement(handle, "/VTKFile", "PolyData");

    for (unsigned int iobj = 1; iobj <= getNObjects(); ++iobj ) {
        writeVTKPiece(handle, iobj);
    }
}

void setMinMax(const CTiglPoint& p, double* oldmin, double* oldmax)
{
    if (p.x > *oldmax) {
        *oldmax = p.x;
    }

    if (p.y > *oldmax) {
        *oldmax = p.y;
    }

    if (p.z > *oldmax) {
        *oldmax = p.z;
    }

    if (p.x < *oldmin) {
        *oldmin = p.x;
    }

    if (p.y < *oldmin) {
        *oldmin = p.y;
    }

    if (p.z < *oldmin) {
        *oldmin = p.z;
    }
}

// writes the polygon data of a surface (in vtk they call it piece)
void CTiglPolyData::writeVTKPiece(TixiDocumentHandle& handle, unsigned int iObject)
{

    CTiglPolyObject& co = switchObject(iObject);

    if (co.getNPolygons() == 0) {
        return;
    }

    // count number of vertices - this is not necessarily the number of points
    int nvert = 0;
    for (unsigned int i = 0; i < co.getNPolygons(); ++i) {
        nvert += co.getNPointsOfPolygon(i);
    }

    if (nvert <= 0) {
        return;
    }

    // surface specific stuff
    tixiCreateElement(handle, "/VTKFile/PolyData","Piece");

    char piecepath[512];
    snprintf(piecepath, 512, "/VTKFile/PolyData/Piece[%d]", iObject);

    tixiAddIntegerAttribute(handle, piecepath, "NumberOfPoints", co.getNVertices(), "%d");
    tixiAddIntegerAttribute(handle, piecepath, "NumberOfVerts",  0, "%d");
    tixiAddIntegerAttribute(handle, piecepath, "NumberOfLines",  0, "%d");
    tixiAddIntegerAttribute(handle, piecepath, "NumberOfStrips", 0, "%d");
    tixiAddIntegerAttribute(handle, piecepath, "NumberOfPolys",  co.getNPolygons(), "%d");

    tixiCreateElement(handle, piecepath, "Points");

    //points
    {
        unsigned int nPoints = co.getNVertices();
        std::stringstream stream1;
        stream1 << std::endl <<   "         ";
        double min_coord = DBL_MAX, max_coord = DBL_MIN;
        for (unsigned int i = 0; i < nPoints; ++i) {
            const CTiglPoint& p = co.getVertexPoint(i);
            setMinMax(p, &min_coord, &max_coord);
            stream1 << "    " <<  p.x << " " << p.y << " " << p.z << std::endl;
            stream1 << "         ";
        }
        char tmpPath[512];
        snprintf(tmpPath, 512, "%s/Points", piecepath);
        tixiAddTextElement(handle, tmpPath, "DataArray", stream1.str().c_str());
        snprintf(tmpPath, 512,  "%s/Points/DataArray", piecepath);
        tixiAddTextAttribute(handle, tmpPath, "type", "Float64");
        tixiAddTextAttribute(handle, tmpPath, "Name", "Points");
        tixiAddTextAttribute(handle, tmpPath, "NumberOfComponents", "3");
        tixiAddTextAttribute(handle, tmpPath, "format", "ascii");
        tixiAddDoubleAttribute(handle, tmpPath, "RangeMin", min_coord ,"%f");
        tixiAddDoubleAttribute(handle, tmpPath, "RangeMax", max_coord ,"%f");
    }

    //normals
    if (co.hasNormals()) {
        tixiCreateElement(handle, piecepath, "PointData");
        char tmpPath[512];
        snprintf(tmpPath, 512, "%s/PointData", piecepath);

        tixiAddTextAttribute(handle, tmpPath, "Normals", "surf_normals");

        std::stringstream stream;
        double min_coord = DBL_MAX, max_coord = DBL_MIN;
        stream << endl  << "        ";
        for (unsigned int i=0; i < co.getNVertices(); ++i) {
             const CTiglPoint& n = co.getVertexNormal(i);
             setMinMax(n, &min_coord, &max_coord);
             stream << "    " << n.x << " " << n.y << " "  << n.z << endl;
             stream <<  "        ";
        }

        tixiAddTextElement(handle, tmpPath, "DataArray", stream.str().c_str());
        snprintf(tmpPath, 512, "%s/PointData/DataArray", piecepath);
        tixiAddTextAttribute(handle, tmpPath, "type", "Float64");
        tixiAddTextAttribute(handle, tmpPath, "Name", "surf_normals");
        tixiAddTextAttribute(handle, tmpPath, "NumberOfComponents", "3");
        tixiAddTextAttribute(handle, tmpPath, "format", "ascii");
        tixiAddDoubleAttribute(handle, tmpPath, "RangeMin", min_coord ,"%f");
        tixiAddDoubleAttribute(handle, tmpPath, "RangeMax", max_coord ,"%f");
    }

    //polygons
    {
        tixiCreateElement(handle, piecepath, "Polys");
        std::stringstream stream2;
        stream2 << std::endl <<   "        ";
        for (unsigned int iPoly = 0; iPoly < co.getNPolygons(); ++iPoly) {
            stream2 <<     "    ";
            for (unsigned int jPoint = 0; jPoint < co.getNPointsOfPolygon(iPoly); ++jPoint ) {
                stream2 << co.getVertexIndexOfPolygon(jPoint, iPoly) << " ";
            }
            stream2  << std::endl <<  "        ";;
        }

        char tmpPath[512];
        snprintf(tmpPath, 512, "%s/Polys", piecepath);
        tixiAddTextElement(handle, tmpPath, "DataArray", stream2.str().c_str());
        snprintf(tmpPath, 512, "%s/Polys/DataArray", piecepath);
        tixiAddTextAttribute(handle,tmpPath, "type", "Int32");
        tixiAddTextAttribute(handle, tmpPath, "Name", "connectivity");
        tixiAddTextAttribute(handle, tmpPath, "format", "ascii");
        tixiAddIntegerAttribute(handle, tmpPath, "RangeMin", 0 ,"%d");
        tixiAddIntegerAttribute(handle, tmpPath, "RangeMax", co.getNVertices()-1,"%d");
    }

    //offset
    {
        unsigned int next = 0;
        std::stringstream stream3;
        for (unsigned int i = 0; i < co.getNPolygons(); i ++) {
            if ((i % 10 == 0) && (i != (co.getNPolygons() - 1))) {
                stream3 << endl << "            ";
            }
            next += co.getNPointsOfPolygon(i);
            stream3 << " " << next;
    }
    stream3 << endl << "        ";
    char tmpPath[512];
    snprintf(tmpPath, 512, "%s/Polys", piecepath);
    tixiAddTextElement(handle, tmpPath, "DataArray", stream3.str().c_str());
    snprintf(tmpPath, 512, "%s/Polys/DataArray[2]", piecepath);
    tixiAddTextAttribute(handle, tmpPath, "type", "Int32");
    tixiAddTextAttribute(handle, tmpPath, "Name", "offsets");
    tixiAddIntegerAttribute(handle, tmpPath, "RangeMin", co.getNPointsOfPolygon(0) ,"%d");
    tixiAddIntegerAttribute(handle, tmpPath, "RangeMax", nvert,"%d");
    }
    
    // write cell data
    if (currentObject().getNumberOfPolyRealData() > 0) {
        tixiCreateElement(handle, piecepath, "CellData");
        char tmpPath[512];
        snprintf(tmpPath, 512, "%s/CellData", piecepath);
        
        for (unsigned int iData = 0; iData < currentObject().getNumberOfPolyRealData(); ++iData) {
            const char * dataField = currentObject().getPolyDataFieldName(iData);
            std::stringstream stream;
            for (unsigned long jPoly = 0; jPoly < currentObject().getNPolygons(); ++jPoly) {
                stream << currentObject().getPolyDataReal(jPoly, dataField) << " ";
            }
            tixiAddTextElement(handle, tmpPath, "DataArray", stream.str().c_str());
            char path[512];
            snprintf(path, 512, "%s/DataArray[%d]", tmpPath, iData+1);
            tixiAddTextAttribute(handle, path, "type", "Float64");
            tixiAddTextAttribute(handle, path, "Name", dataField);
            tixiAddTextAttribute(handle, path, "NumberOfComponents", "1");
            tixiAddTextAttribute(handle, path, "format", "ascii");
            tixiAddDoubleAttribute(handle, path, "RangeMin", 0. ,"%f");
            tixiAddDoubleAttribute(handle, path, "RangeMax", 1. ,"%f");
            
        }
        
    }

    // write metadata
    if (currentObject().hasMetadata()) {
        std::stringstream stream4;
        stream4 << endl  << "        ";
        for (unsigned int i = 0; i < co.getNPolygons(); i ++) {
            stream4 << "    " << co.getPolyMetadata(i) << endl;
            stream4 << "        ";
        }
        char tmpPath[512];
        snprintf(tmpPath, 512, "%s/Polys", piecepath);
        tixiAddTextElement(handle, tmpPath, "MetaData", stream4.str().c_str());
        snprintf(tmpPath, 512, "%s/Polys/MetaData", piecepath);
        tixiAddTextAttribute(handle,  tmpPath, "elements", currentObject().getMetadataElements() );
    }

}

// --------------------------------------------------------------------------//

void PolyIndexList::addPoint(int index)
{
    // dont add same point twice
    if (pindex.size() == 0 || pindex.back() != index) {
         pindex.push_back(index);
    }
}

void PolyIndexList::repair()
{
    if (pindex.size() > 0 && pindex.front() == pindex.back()) {
        pindex.pop_back();
    }
    if (pindex.size() < 3) {
        std::cerr << "ERROR: polygon " << myid << " must contain at least 3 points!" << pindex.size()<< std::endl;
        exit(1);
    }
}


//--------------------------------------------------------------------------//

CTiglPolyObject::CTiglPolyObject()
{
    impl = new ObjectImpl;
}

CTiglPolyObject::~CTiglPolyObject()
{
    delete impl;
}

unsigned long CTiglPolyObject::addPointNormal(const CTiglPoint &p, const CTiglPoint &n)
{
    return impl->addPointNorm(p,n);
}

void CTiglPolyObject::addPolygon(const CTiglPolygon & polygon)
{
    impl->addPolygon(polygon);
}

unsigned long CTiglPolyObject::addTriangleByVertexIndex(unsigned long i1, unsigned long i2, unsigned long i3)
{
    return impl->addTriangleByVertexIndex(i1, i2, i3);
}

unsigned long CTiglPolyObject::getNPointsOfPolygon(unsigned long ipoly) const 
{
    return impl->getNPointsOfPolygon(ipoly);
}

unsigned long CTiglPolyObject::getNPolygons() const
{
    return impl->getNPolygons();
}

unsigned long CTiglPolyObject::getNVertices() const
{
    return impl->pPoints.size();
}

void CTiglPolyObject::enableNormals(bool normals_enabled)
{
    impl->has_normals = normals_enabled;
}

bool CTiglPolyObject::hasNormals() const 
{
    return impl->has_normals;
}

unsigned long CTiglPolyObject::getVertexIndexOfPolygon(unsigned long iPoint, unsigned long iPoly) const 
{
    if (iPoly < getNPolygons()) {
        if (iPoint < getNPointsOfPolygon(iPoly)) {
            return impl->polys[iPoly].getPointIndex(iPoint);
        }
        else {
            throw tigl::CTiglError("Illegal Point Index at CTiglPolyObject::getVertexIndexOfPolygon", TIGL_INDEX_ERROR);
        }
    }
    else {
        throw tigl::CTiglError("Illegal Polygon Index at CTiglPolyObject::getVertexIndexOfPolygon", TIGL_INDEX_ERROR);
    }
}

const CTiglPoint& CTiglPolyObject::getVertexNormal(unsigned long iVertexIndex) const 
{
    if (iVertexIndex < getNVertices()) {
        return impl->pPoints[iVertexIndex]->getNormal();
    }
    else {
        throw tigl::CTiglError("Illegal Vertex Index at CTiglPolyObject::getVertexNormal", TIGL_INDEX_ERROR);
    }
}

const CTiglPoint& CTiglPolyObject::getVertexPoint(unsigned long iVertexIndex) const 
{
    if (iVertexIndex < getNVertices()) {
        return impl->pPoints[iVertexIndex]->getPoint();
    }
    else {
        throw tigl::CTiglError("Illegal Vertex Index at CTiglPolyObject::getVertexNormal", TIGL_INDEX_ERROR);
    }
}

bool CTiglPolyObject::hasMetadata() const 
{
    return impl->has_metadata;
}

const char * CTiglPolyObject::getMetadataElements() const 
{
    return impl->metaDataElements.c_str();
}

void CTiglPolyObject::setMetadataElements(const char * elems) 
{
    impl->metaDataElements = elems;
}

const char * CTiglPolyObject::getPolyMetadata(unsigned long iPoly) const 
{
    if (iPoly < getNPolygons()) {
        return impl->polys[iPoly].getMetadata().c_str();
    }
    else {
        throw tigl::CTiglError("Illegal Polygon Index at CTiglPolyObject::getPolyMetadata", TIGL_INDEX_ERROR);
    }
}

void CTiglPolyObject::setPolyMetadata(unsigned long iPoly, const char * txt)
{
    if (iPoly < getNPolygons()) {
        impl->polys[iPoly].setMetadata(txt);
        impl->has_metadata = true;
    }
    else {
        throw tigl::CTiglError("Illegal Polygon Index at CTiglPolyObject::setPolyMetadata", TIGL_INDEX_ERROR);
    }
}

void CTiglPolyObject::setVertexDataReal(unsigned long iVertexIndex, const char *dataName, double value)
{
    if (iVertexIndex < getNVertices()) {
        //insert into elems
        impl->vertexDataElems.insert(dataName);
        
        impl->pPoints[iVertexIndex]->setRealData(dataName, value);
    }
    else {
        throw tigl::CTiglError("Illegal Vertex Index at CTiglPolyObject::setVertexDataReal", TIGL_INDEX_ERROR);
    }
}

double CTiglPolyObject::getVertexDataReal(unsigned long iVertexIndex, const char *dataName) const
{
    if (iVertexIndex < getNVertices()) {
        return impl->pPoints[iVertexIndex]->getRealData(dataName);
    }
    else {
        throw tigl::CTiglError("Illegal Vertex Index at CTiglPolyObject::getVertexDataReal", TIGL_INDEX_ERROR);
    }
}

void CTiglPolyObject::setPolyDataReal(unsigned long iPolyIndex, const char *dataName, double value)
{
    if (iPolyIndex < getNPolygons()) {
        //insert into elems
        impl->polyDataElems.insert(dataName);
        
        impl->polys[iPolyIndex].setRealData(dataName, value);
    }
    else {
        throw tigl::CTiglError("Illegal Polygon Index at CTiglPolyObject::setPolyDataReal", TIGL_INDEX_ERROR);
    }
}

double CTiglPolyObject::getPolyDataReal(unsigned long iPolyIndex, const char *dataName) const
{
    if (iPolyIndex < getNPolygons()) {
        return impl->polys[iPolyIndex].getRealData(dataName);
    }
    else {
        throw tigl::CTiglError("Illegal Polygon Index at CTiglPolyObject::getPolyDataReal", TIGL_INDEX_ERROR);
    }
}

// returns the number if different polygon data entries 
unsigned int CTiglPolyObject::getNumberOfPolyRealData() const 
{
    return impl->polyDataElems.size();
}

// retuns the  name of the ith data field (i = 0 .. getNumberPolyReadlData - 1)
const char * CTiglPolyObject::getPolyDataFieldName(unsigned long iField) const 
{
    if (iField < getNumberOfPolyRealData()) {
        std::set<std::string>::iterator it = impl->polyDataElems.begin();
        for (unsigned long i = 0; i < iField; ++i) {
            ++it;
        }
        return it->c_str();
    }
    else {
        throw tigl::CTiglError("Illegal Data Field Index at CTiglPolyObject::getPolyDataFieldName", TIGL_INDEX_ERROR);
    }
}


//---------------------------------------------------------------------------//

CTiglPolygon::CTiglPolygon()
{
    _metadata.clear();
    _points.clear();
    _normals.clear();
}

unsigned int CTiglPolygon::getNPoints() const
{
    return _points.size();
}

void CTiglPolygon::addPoint(const CTiglPoint & p)
{
    _points.push_back(p);
}

void CTiglPolygon::addNormal(const  CTiglPoint & n)
{
    _normals.push_back(n);
}

CTiglPoint& CTiglPolygon::getPoint(unsigned int index)
{
    return _points.at(index);
}

const CTiglPoint& CTiglPolygon::getPointConst(unsigned int index) const
{
    return _points.at(index);
}

const CTiglPoint& CTiglPolygon::getNormConst(unsigned int index) const
{
    return _normals.at(index);
}

void CTiglPolygon::setMetadata(const char * text)
{
    _metadata = text;
}

const char * CTiglPolygon::getMetadata() const
{
    return _metadata.c_str();
}

//--------------------------------------------------------------//

void ObjectImpl::addPointNorm(const CTiglPoint& p, const CTiglPoint& n, long polynum)
{
    unsigned long index = addPointNorm(p,n);

    // now insert point into polygon list
    if (polynum > (long) polys.size()) {
        polys.push_back(PolyIndexList(polynum));
    }
    assert(polynum == polys.size());
    polys.at(polynum-1).addPoint(index);
}

unsigned long ObjectImpl::addPointNorm(const CTiglPoint& p, const CTiglPoint& n) 
{
    using namespace std;

    //check if point is already in pointlist
    unsigned int index = pointlist.size();
    std::pair<PointMap::iterator,bool> ret;

    ret = pointlist.insert(std::pair<PointImpl, int>(PointImpl(p,n),index));
    index = ret.first->second;
/*#ifndef NDEBUG
    if(ret.second == false){
        double dist = ret.first->first.dist2(p);
        assert(pointlist.size() == 0 ||  dist < 1e-9);
    }
#endif*/
    if (ret.second == true) {
        // a new point was inserted, we have to keep track
        PointImpl * ptmp = (PointImpl*)&ret.first->first;
        pPoints.push_back(ptmp);
    }
    
    return index;
}

unsigned long ObjectImpl::addTriangleByVertexIndex(unsigned long i1, unsigned long i2, unsigned long i3 )
{
    unsigned long nPolys = polys.size();
    polys.push_back(PolyIndexList(nPolys));
    
    std::vector<PolyIndexList>::iterator itLastPoly = polys.end()-1;
    itLastPoly->addPoint(i1);
    itLastPoly->addPoint(i2);
    itLastPoly->addPoint(i3);
    
    return nPolys;
}


void ObjectImpl::addPolygon(const CTiglPolygon & poly)
{
    long polynum = polys.size() + 1;
    if (!has_normals) {
        for (unsigned long i = 0 ; i < poly.getNPoints(); ++i) {
            CTiglPoint n(1,0,0);
            addPointNorm(poly.getPointConst(i), n, polynum);
        }
    }
    else {
        for (unsigned long i = 0 ; i < poly.getNPoints(); ++i) {
            addPointNorm(poly.getPointConst(i), poly.getNormConst(i), polynum);
        }
    }
    assert(polynum == polys.size());
    polys.at(polynum-1).setMetadata(poly.getMetadata());
}


unsigned long ObjectImpl::getNPolygons() const 
{
    return polys.size();
}

unsigned long ObjectImpl::getNPointsOfPolygon(unsigned long ipoly) const 
{
    if (ipoly < getNPolygons()) {
        return polys[ipoly].getNVert();
    }
    else {
        throw tigl::CTiglError("Illegal Polygon Index at SurfaceImpl::getNPointsOfPolygon", TIGL_INDEX_ERROR);
    }
}
