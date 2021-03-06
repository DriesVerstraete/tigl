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

#include <CCPACSGuideCurveProfile.h>
#include "CPACSGuideCurveProfiles.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "CTiglUIDManager.h"
#include "TixiHelper.h"

namespace tigl
{
    namespace generated
    {
        CPACSGuideCurveProfiles::CPACSGuideCurveProfiles(CTiglUIDManager* uidMgr) :
            m_uidMgr(uidMgr) {}
        
        CPACSGuideCurveProfiles::~CPACSGuideCurveProfiles() {}
        
        CTiglUIDManager& CPACSGuideCurveProfiles::GetUIDManager()
        {
            return *m_uidMgr;
        }
        
        const CTiglUIDManager& CPACSGuideCurveProfiles::GetUIDManager() const
        {
            return *m_uidMgr;
        }
        
        void CPACSGuideCurveProfiles::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
        {
            // read element guideCurveProfile
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/guideCurveProfile")) {
                tixihelper::TixiReadElements(tixiHandle, xpath + "/guideCurveProfile", m_guideCurveProfiles, m_uidMgr);
            }
            
        }
        
        void CPACSGuideCurveProfiles::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
        {
            // write element guideCurveProfile
            tixihelper::TixiSaveElements(tixiHandle, xpath + "/guideCurveProfile", m_guideCurveProfiles);
            
        }
        
        const std::vector<unique_ptr<CCPACSGuideCurveProfile> >& CPACSGuideCurveProfiles::GetGuideCurveProfiles() const
        {
            return m_guideCurveProfiles;
        }
        
        std::vector<unique_ptr<CCPACSGuideCurveProfile> >& CPACSGuideCurveProfiles::GetGuideCurveProfiles()
        {
            return m_guideCurveProfiles;
        }
        
    }
}
