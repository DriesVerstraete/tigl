/* 
* Copyright (C) 2007-2013 German Aerospace Center (DLR/SC)
*
* Created: 2010-08-13 Markus Litz <Markus.Litz@dlr.de>
* Changed: $Id$ 
*
* Version: $Revision$
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
/**
* @file
* @brief  Export routines for CPACS configurations.
*/

// standard libraries
#include <iostream>
#include <algorithm>

#include "CTiglLogging.h"
#include "CTiglExportVtk.h"
#include "CCPACSConfiguration.h"
#include "CTiglRelativelyPositionedComponent.h"
#include "CTiglAbstractSegment.h"
#include "CCPACSWing.h"
#include "CCPACSConfiguration.h"
#include "CCPACSConfigurationManager.h"
#include "CCPACSWingSegment.h"
#include "CNamedShape.h"

// algorithms
#include "BRepMesh.hxx"


#include "CTiglPolyData.h"
#include "CTiglTriangularizer.h"

namespace
{
    tigl::CTiglTriangularizerOptions getOptions(const tigl::CTiglExportVtk& /* exporter */)
    {
        tigl::CTiglTriangularizerOptions options;
        options.setNormalsEnabled(tigl::CTiglExportVtk::normalsEnabled);

        return options ;
    }

    std::string to_lower(const std::string& str)
    {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);

        return result;
    }
}

namespace tigl 
{

bool CTiglExportVtk::normalsEnabled = true;

// Constructor
CTiglExportVtk::CTiglExportVtk(CCPACSConfiguration& config)
    :myConfig(config)
{
}

// Destructor
CTiglExportVtk::~CTiglExportVtk()
{
}


// Exports a by index selected wing, boolean fused and meshed, as STL file
void CTiglExportVtk::ExportMeshedWingVTKByIndex(const int wingIndex, const std::string& filename, const double deflection)
{
    const std::string& wingUID = myConfig.GetWing(wingIndex).GetUID();
    ExportMeshedWingVTKByUID(wingUID, filename, deflection);
}

// Exports a by UID selected wing, boolean fused and meshed, as STL file
void CTiglExportVtk::ExportMeshedWingVTKByUID(const std::string& wingUID, const std::string& filename, const double deflection)
{
    tigl::CCPACSWing& wing = myConfig.GetWing(wingUID);
    CTiglTriangularizer wingTrian(wing, deflection, SEGMENT_INFO, getOptions(*this));
    wingTrian.writeVTK(filename.c_str());
}



// Exports a by index selected fuselage, boolean fused and meshed, as VTK file
void CTiglExportVtk::ExportMeshedFuselageVTKByIndex(const int fuselageIndex, const std::string& filename, const double deflection)
{
    CTiglRelativelyPositionedComponent & component = myConfig.GetFuselage(fuselageIndex);
    ExportMeshedFuselageVTKByUID(component.GetDefaultedUID(), filename, deflection);
}

// Exports a by UID selected fuselage, boolean fused and meshed, as VTK file
void CTiglExportVtk::ExportMeshedFuselageVTKByUID(const std::string& fuselageUID, const std::string& filename, const double deflection)
{
    CTiglRelativelyPositionedComponent & component = myConfig.GetFuselage(fuselageUID);
    const TopoDS_Shape& shape = component.GetLoft()->Shape();
    CTiglTriangularizer trian(shape, deflection, getOptions(*this));
    trian.writeVTK(filename.c_str());
}


// Exports a whole geometry, boolean fused and meshed, as VTK file
void CTiglExportVtk::ExportMeshedGeometryVTK(const std::string& filename, const double deflection)
{
    tigl::CTiglTriangularizer trian(myConfig, true, deflection, SEGMENT_INFO, getOptions(*this));
    trian.writeVTK(filename.c_str());
}

/************* Simple ones *************************/
// Exports a by UID selected wing, boolean fused and meshed, as STL file
void CTiglExportVtk::ExportMeshedWingVTKSimpleByUID(const std::string& wingUID, const std::string& filename, const double deflection)
{
    CCPACSWing & component = dynamic_cast<CCPACSWing&>(myConfig.GetWing(wingUID));
    TopoDS_Shape& loft = component.GetLoftWithLeadingEdge();
    CTiglTriangularizer loftTrian(loft, deflection, getOptions(*this));
    loftTrian.writeVTK(filename.c_str());
}

/************* Simple ones *************************/
// Exports a by UID selected wing, boolean fused and meshed, as STL file
void CTiglExportVtk::ExportMeshedWingVTKSimpleByIndex(const int wingIndex, const std::string& filename, const double deflection)
{
    const std::string& wingUID = myConfig.GetWing(wingIndex).GetUID();
    ExportMeshedWingVTKSimpleByUID(wingUID, filename, deflection);
}

// Exports a by UID selected fuselage, boolean fused and meshed, as VTK file
void CTiglExportVtk::ExportMeshedFuselageVTKSimpleByUID(const std::string& fuselageUID, const std::string& filename, const double deflection)
{
    CTiglRelativelyPositionedComponent & component = myConfig.GetFuselage(fuselageUID);
    const TopoDS_Shape& shape = component.GetLoft()->Shape();
    CTiglTriangularizer loftTrian(shape, deflection, getOptions(*this));
    loftTrian.writeVTK(filename.c_str());
}

// Exports a by UID selected fuselage, boolean fused and meshed, as VTK file
void CTiglExportVtk::ExportMeshedFuselageVTKSimpleByIndex(const int fuselageIndex, const std::string& filename, const double deflection)
{
    const std::string& fuselageUID = myConfig.GetFuselage(fuselageIndex).GetUID();
    ExportMeshedFuselageVTKSimpleByUID(fuselageUID, filename, deflection);
}


// Exports a whole geometry, boolean fused and meshed, as VTK file
void CTiglExportVtk::ExportMeshedGeometryVTKSimple(const std::string& filename, const double deflection)
{
    tigl::CTiglTriangularizer trian(myConfig, true, deflection, NO_INFO, getOptions(*this));
    trian.writeVTK(filename.c_str());
}

// Exports a whole geometry, not fused and meshed, as VTK file
void CTiglExportVtk::ExportMeshedGeometryVTKNoFuse(const std::string& filename, const double deflection)
{
    tigl::CTiglTriangularizer trian(myConfig, false, deflection, NO_INFO, getOptions(*this));
    trian.writeVTK(filename.c_str());
}

void CTiglExportVtk::SetOptions(const std::string &key, const std::string &value)
{
    if (key == "normals_enabled") {
        if (value == "1" || to_lower(value) == "true") {
            CTiglExportVtk::normalsEnabled = true;
        }
        else if (value == "0" || to_lower(value) == "false") {
            CTiglExportVtk::normalsEnabled = false;
        }
        else {
            throw CTiglError("Wrong value for 'normals_enabled' in vtk export: " + value);
        }
    }

    else {
        throw CTiglError("Invalid key in vtk export: " + key);
    }
}

} // end namespace tigl
