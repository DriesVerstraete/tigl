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

#include "CPACSToolspecific.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "TixiHelper.h"

namespace tigl
{
    namespace generated
    {
        CPACSToolspecific::CPACSToolspecific() {}
        
        CPACSToolspecific::~CPACSToolspecific() {}
        
        void CPACSToolspecific::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
        {
            // read element cFD
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/cFD")) {
                m_cFD = boost::in_place();
                try {
                    m_cFD->ReadCPACS(tixiHandle, xpath + "/cFD");
                } catch(const std::exception& e) {
                    LOG(ERROR) << "Failed to read cFD at xpath " << xpath << ": " << e.what();
                    m_cFD = boost::none;
                }
            }
            
        }
        
        void CPACSToolspecific::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
        {
            // write element cFD
            if (m_cFD) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/cFD");
                m_cFD->WriteCPACS(tixiHandle, xpath + "/cFD");
            } else {
                if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/cFD")) {
                    tixihelper::TixiRemoveElement(tixiHandle, xpath + "/cFD");
                }
            }
            
        }
        
        const boost::optional<CPACSCFDTool>& CPACSToolspecific::GetCFD() const
        {
            return m_cFD;
        }
        
        boost::optional<CPACSCFDTool>& CPACSToolspecific::GetCFD()
        {
            return m_cFD;
        }
        
    }
}
