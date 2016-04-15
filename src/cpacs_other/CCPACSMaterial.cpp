/* 
* Copyright (C) 2007-2013 German Aerospace Center (DLR/SC)
*
* Created: 2013-05-28 Martin Siggel <Martin.Siggel@dlr.de>
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
*/

#include "CCPACSMaterial.h"

#include "CTiglError.h"
#include "CTiglLogging.h"
#include "TixiSaveExt.h"

namespace tigl
{

CCPACSMaterial::CCPACSMaterial()
{
    Cleanup();
}

void CCPACSMaterial::Cleanup()
{
    uid = "UID_NOTSET";
    thickness = -1.;
    thicknessScaling = 1.;
    isvalid = false;
    is_composite = false;
    // [[CAS_AES]] added orthotropy direction
    orthotropyDirection = CTiglPoint();
}

void CCPACSMaterial::ReadCPACS(TixiDocumentHandle tixiHandle, const std::string &materialXPath)
{
    Cleanup();
    
    // check path
    if ( tixiCheckElement(tixiHandle, materialXPath.c_str()) != SUCCESS) {
        LOG(ERROR) << "Material definition" << materialXPath << " not found in CPACS file!" << std::endl;
        return;
    }
    
    // test whether composite or normal material
    std::string tempstring = materialXPath + "/materialUID";
    char * matUID = NULL;
    if (tixiGetTextElement(tixiHandle, tempstring.c_str(), &matUID) == SUCCESS){
        uid = matUID;
        is_composite = false;
    }
    else if (tixiGetTextElement(tixiHandle, std::string(materialXPath + "/compositeUID").c_str(), &matUID) == SUCCESS){
        uid = matUID;
        is_composite = true;
    }
    else {
        throw CTiglError("Neither Material UID nor Composite UID  specified in " + materialXPath, TIGL_ERROR);
    }
    
    // get thickness (not mandatory)
    tempstring = materialXPath + "/thickness";
    if (tixiCheckElement(tixiHandle, tempstring.c_str())== SUCCESS) {
       if (tixiGetDoubleElement(tixiHandle, tempstring.c_str(), &thickness) != SUCCESS) {
           LOG(ERROR) << "Invalid material thickness in " << materialXPath;
       }
    }
    else if (tixiCheckElement(tixiHandle, std::string(materialXPath + "/thicknessScaling").c_str())== SUCCESS) {
       if (tixiGetDoubleElement(tixiHandle, std::string(materialXPath + "/thicknessScaling").c_str(), &thicknessScaling) != SUCCESS) {
           LOG(ERROR) << "Invalid composite thickness scaling in " << materialXPath;
       }
    }
    else {
        if (!isComposite()) {
            LOG(INFO) << "Thickness of Material " << materialXPath << " not set.";
        }
        else {
            LOG(INFO) << "Thickness scaling of Composite Material " << materialXPath << " not set.";
        }
    }
    
    // [[CAS_AES]] added orthotropy direction
    if (isComposite()) {
        std::string tempString;
        char* path;
        ReturnCode tixiRet;
        int count;

        double dTemp = 0.0;

        tempString = materialXPath + "/orthotropyDirection";
        path = const_cast<char*>(tempString.c_str());
        tixiRet = tixiGetNamedChildrenCount(tixiHandle, path, "x", &count);

        if (count == 0)
        {
            dTemp = 0.0;
        }
        else
        {
            tempString = materialXPath + "/orthotropyDirection/x";
            path = const_cast<char*>(tempString.c_str());
            tixiRet = tixiGetDoubleElement(tixiHandle, path, &dTemp);
    
            if (tixiRet != SUCCESS) {
                throw CTiglError("Error: Error during read of <orthotropyDirection/x> in CCPACSMaterial::ReadCPACS!", TIGL_XML_ERROR);
            }
        }
        orthotropyDirection.x = dTemp;
        

        tempString = materialXPath + "/orthotropyDirection";
        path = const_cast<char*>(tempString.c_str());
        tixiRet = tixiGetNamedChildrenCount(tixiHandle, path, "y", &count);

        if (count == 0)
        {
            dTemp = 0.0;
        }
        else
        {
            tempString = materialXPath + "/orthotropyDirection/y";
            path = const_cast<char*>(tempString.c_str());
            tixiRet = tixiGetDoubleElement(tixiHandle, path, &dTemp);
    
            if (tixiRet != SUCCESS) {
                throw CTiglError("Error: Error during read of <orthotropyDirection/y> in CCPACSMaterial::ReadCPACS!", TIGL_XML_ERROR);
            }
        }
        orthotropyDirection.y = dTemp;

        tempString = materialXPath + "/orthotropyDirection";
        path = const_cast<char*>(tempString.c_str());
        tixiRet = tixiGetNamedChildrenCount(tixiHandle, path, "z", &count);

        if (count == 0)
        {
            dTemp = 0.0;
        }
        else
        {
            tempString = materialXPath + "/orthotropyDirection/z";
            path = const_cast<char*>(tempString.c_str());
            tixiRet = tixiGetDoubleElement(tixiHandle, path, &dTemp);
    
            if (tixiRet != SUCCESS) {
                throw CTiglError("Error: Error during read of <orthotropyDirection/z> in CCPACSMaterial::ReadCPACS!", TIGL_XML_ERROR);
            }
        }
        orthotropyDirection.z = dTemp;
    }

    isvalid = true;
}

void CCPACSMaterial::WriteCPACS(TixiDocumentHandle tixiHandle, const std::string& xpath)
{
    std::string path;
    std::string elementPath;

    if (!isComposite()) {
        // Save isotropicMaterial
        // Save materialUID
        TixiSaveExt::TixiSaveTextElement(tixiHandle, xpath.c_str(), "materialUID", GetUID().c_str());

        // Save thickness
        TixiSaveExt::TixiSaveDoubleElement(tixiHandle, xpath.c_str(), "thickness", GetThickness(), NULL);
    }
    else {
        // Save compositeUID
        TixiSaveExt::TixiSaveTextElement(tixiHandle, xpath.c_str(), "compositeUID", GetUID().c_str());

        // Save thicknessScaling
        TixiSaveExt::TixiSaveDoubleElement(tixiHandle, xpath.c_str(), "thicknessScaling", GetThicknessScaling(), NULL);

        // create element ortotropyDirection
        TixiSaveExt::TixiSaveElement(tixiHandle, xpath.c_str(), "orthotropyDirection");

        // Save orthotropyDirection/x
        std::string subpath = xpath + "/orthotropyDirection";

        TixiSaveExt::TixiSaveDoubleElement(tixiHandle, subpath.c_str(), "x", orthotropyDirection.x, NULL);

        TixiSaveExt::TixiSaveDoubleElement(tixiHandle, subpath.c_str(), "y", orthotropyDirection.y, NULL);

        TixiSaveExt::TixiSaveDoubleElement(tixiHandle, subpath.c_str(), "z", orthotropyDirection.z, NULL);
    }
}

void CCPACSMaterial::Invalidate()
{
    isvalid = false;
}

bool CCPACSMaterial::isComposite() const
{
    return is_composite;
}

// [[CAS_AES]] added setter for composite
void CCPACSMaterial::SetComposite(bool composite)
{
    is_composite = composite;
}

bool CCPACSMaterial::IsValid() const
{
    return isvalid;
}

const std::string& CCPACSMaterial::GetUID() const
{
    return uid;
}

double CCPACSMaterial::GetThickness() const
{
    return thickness;
}

double CCPACSMaterial::GetThicknessScaling() const
{
    return thicknessScaling;
}

// [[CAS_AES]] Setter of the orthotropyDirection object
void CCPACSMaterial::SetOrthotropyDirection(tigl::CTiglPoint D){
    orthotropyDirection = D;
}

// [[CAS_AES]] added getter for orthotropy direction
const CTiglPoint& CCPACSMaterial::GetOrthotropyDirection() const
{
    return orthotropyDirection;
}

// [[CAS_AES]] added setter for UID
void CCPACSMaterial::SetUID(const std::string& uid)
{
    this->uid = uid;
}

// [[CAS_AES]] added setter for thicknes
void CCPACSMaterial::SetThickness(double thickness)
{
    this->thickness = thickness;
}

// [[CAS_AES]] added setter for thickness scaling
void CCPACSMaterial::SetThicknessScaling(double thicknessScaling)
{
    this->thicknessScaling = thicknessScaling;
}

} // namespace tigl
