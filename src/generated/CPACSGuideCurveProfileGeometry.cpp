// Copyright (c) 2016 RISC Software GmbH
//
// This file was generated by CPACSGen from CPACS XML Schema (c) German Aerospace Center (DLR/SC).
// Do not edit, all changes are lost when files are re-generated.
//
// Licensed under the Apache License, Version 2.0 (the "License")
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "CPACSGuideCurveProfileGeometry.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "CTiglUIDManager.h"
#include "TixiHelper.h"

namespace tigl
{
    namespace generated
    {
        CPACSGuideCurveProfileGeometry::CPACSGuideCurveProfileGeometry(CTiglUIDManager* uidMgr) :
            m_uidMgr(uidMgr) {}
        
        CPACSGuideCurveProfileGeometry::~CPACSGuideCurveProfileGeometry()
        {
            if (m_uidMgr) m_uidMgr->TryUnregisterObject(m_uID);
        }
        
        CTiglUIDManager& CPACSGuideCurveProfileGeometry::GetUIDManager()
        {
            return *m_uidMgr;
        }
        
        const CTiglUIDManager& CPACSGuideCurveProfileGeometry::GetUIDManager() const
        {
            return *m_uidMgr;
        }
        
        void CPACSGuideCurveProfileGeometry::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
        {
            // read attribute symmetry
            if (tixihelper::TixiCheckAttribute(tixiHandle, xpath, "symmetry")) {
                m_symmetry = stringToTiglSymmetryAxis(tixihelper::TixiGetAttribute<std::string>(tixiHandle, xpath, "symmetry"));
            }
            
            // read attribute uID
            if (tixihelper::TixiCheckAttribute(tixiHandle, xpath, "uID")) {
                m_uID = tixihelper::TixiGetAttribute<std::string>(tixiHandle, xpath, "uID");
                if (m_uID.empty()) {
                    LOG(WARNING) << "Required attribute uID is empty at xpath " << xpath;
                }
            }
            else {
                LOG(ERROR) << "Required attribute uID is missing at xpath " << xpath;
            }
            
            // read element name
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/name")) {
                m_name = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/name");
                if (m_name.empty()) {
                    LOG(WARNING) << "Required element name is empty at xpath " << xpath;
                }
            }
            else {
                LOG(ERROR) << "Required element name is missing at xpath " << xpath;
            }
            
            // read element description
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/description")) {
                m_description = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/description");
                if (m_description->empty()) {
                    LOG(WARNING) << "Optional element description is present but empty at xpath " << xpath;
                }
            }
            
            // read element pointList
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/pointList")) {
                m_pointList.ReadCPACS(tixiHandle, xpath + "/pointList");
            }
            else {
                LOG(ERROR) << "Required element pointList is missing at xpath " << xpath;
            }
            
            if (m_uidMgr) m_uidMgr->RegisterObject(m_uID, *this);
        }
        
        void CPACSGuideCurveProfileGeometry::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
        {
            // write attribute symmetry
            if (m_symmetry) {
                tixihelper::TixiSaveAttribute(tixiHandle, xpath, "symmetry", TiglSymmetryAxisToString(*m_symmetry));
            } else {
                if (tixihelper::TixiCheckAttribute(tixiHandle, xpath, "symmetry")) {
                    tixihelper::TixiRemoveAttribute(tixiHandle, xpath, "symmetry");
                }
            }
            
            // write attribute uID
            tixihelper::TixiSaveAttribute(tixiHandle, xpath, "uID", m_uID);
            
            // write element name
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/name");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/name", m_name);
            
            // write element description
            if (m_description) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/description");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/description", *m_description);
            } else {
                if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/description")) {
                    tixihelper::TixiRemoveElement(tixiHandle, xpath + "/description");
                }
            }
            
            // write element pointList
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/pointList");
            m_pointList.WriteCPACS(tixiHandle, xpath + "/pointList");
            
        }
        
        const boost::optional<TiglSymmetryAxis>& CPACSGuideCurveProfileGeometry::GetSymmetry() const
        {
            return m_symmetry;
        }
        
        void CPACSGuideCurveProfileGeometry::SetSymmetry(const TiglSymmetryAxis& value)
        {
            m_symmetry = value;
        }
        
        void CPACSGuideCurveProfileGeometry::SetSymmetry(const boost::optional<TiglSymmetryAxis>& value)
        {
            m_symmetry = value;
        }
        
        const std::string& CPACSGuideCurveProfileGeometry::GetUID() const
        {
            return m_uID;
        }
        
        void CPACSGuideCurveProfileGeometry::SetUID(const std::string& value)
        {
            if (m_uidMgr) {
                m_uidMgr->TryUnregisterObject(m_uID);
                m_uidMgr->RegisterObject(value, *this);
            }
            m_uID = value;
        }
        
        const std::string& CPACSGuideCurveProfileGeometry::GetName() const
        {
            return m_name;
        }
        
        void CPACSGuideCurveProfileGeometry::SetName(const std::string& value)
        {
            m_name = value;
        }
        
        const boost::optional<std::string>& CPACSGuideCurveProfileGeometry::GetDescription() const
        {
            return m_description;
        }
        
        void CPACSGuideCurveProfileGeometry::SetDescription(const std::string& value)
        {
            m_description = value;
        }
        
        void CPACSGuideCurveProfileGeometry::SetDescription(const boost::optional<std::string>& value)
        {
            m_description = value;
        }
        
        const CCPACSPointListRelXYZ& CPACSGuideCurveProfileGeometry::GetPointList() const
        {
            return m_pointList;
        }
        
        CCPACSPointListRelXYZ& CPACSGuideCurveProfileGeometry::GetPointList()
        {
            return m_pointList;
        }
        
    }
}
