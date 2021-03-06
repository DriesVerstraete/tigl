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

#include "CPACSHeader.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "TixiHelper.h"

namespace tigl
{
    namespace generated
    {
        CPACSHeader::CPACSHeader() :
            m_timestamp(0) {}
        
        CPACSHeader::~CPACSHeader() {}
        
        void CPACSHeader::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
        {
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
            
            // read element creator
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/creator")) {
                m_creator = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/creator");
                if (m_creator.empty()) {
                    LOG(WARNING) << "Required element creator is empty at xpath " << xpath;
                }
            }
            else {
                LOG(ERROR) << "Required element creator is missing at xpath " << xpath;
            }
            
            // read element timestamp
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/timestamp")) {
                m_timestamp = tixihelper::TixiGetElement<std::time_t>(tixiHandle, xpath + "/timestamp");
            }
            else {
                LOG(ERROR) << "Required element timestamp is missing at xpath " << xpath;
            }
            
            // read element version
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/version")) {
                m_version = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/version");
                if (m_version.empty()) {
                    LOG(WARNING) << "Required element version is empty at xpath " << xpath;
                }
            }
            else {
                LOG(ERROR) << "Required element version is missing at xpath " << xpath;
            }
            
            // read element cpacsVersion
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/cpacsVersion")) {
                m_cpacsVersion = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/cpacsVersion");
                if (m_cpacsVersion.empty()) {
                    LOG(WARNING) << "Required element cpacsVersion is empty at xpath " << xpath;
                }
            }
            else {
                LOG(ERROR) << "Required element cpacsVersion is missing at xpath " << xpath;
            }
            
            // read element updates
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/updates")) {
                m_updates = boost::in_place();
                try {
                    m_updates->ReadCPACS(tixiHandle, xpath + "/updates");
                } catch(const std::exception& e) {
                    LOG(ERROR) << "Failed to read updates at xpath " << xpath << ": " << e.what();
                    m_updates = boost::none;
                }
            }
            
        }
        
        void CPACSHeader::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
        {
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
            
            // write element creator
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/creator");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/creator", m_creator);
            
            // write element timestamp
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/timestamp");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/timestamp", m_timestamp);
            
            // write element version
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/version");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/version", m_version);
            
            // write element cpacsVersion
            tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/cpacsVersion");
            tixihelper::TixiSaveElement(tixiHandle, xpath + "/cpacsVersion", m_cpacsVersion);
            
            // write element updates
            if (m_updates) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/updates");
                m_updates->WriteCPACS(tixiHandle, xpath + "/updates");
            } else {
                if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/updates")) {
                    tixihelper::TixiRemoveElement(tixiHandle, xpath + "/updates");
                }
            }
            
        }
        
        const std::string& CPACSHeader::GetName() const
        {
            return m_name;
        }
        
        void CPACSHeader::SetName(const std::string& value)
        {
            m_name = value;
        }
        
        const boost::optional<std::string>& CPACSHeader::GetDescription() const
        {
            return m_description;
        }
        
        void CPACSHeader::SetDescription(const std::string& value)
        {
            m_description = value;
        }
        
        void CPACSHeader::SetDescription(const boost::optional<std::string>& value)
        {
            m_description = value;
        }
        
        const std::string& CPACSHeader::GetCreator() const
        {
            return m_creator;
        }
        
        void CPACSHeader::SetCreator(const std::string& value)
        {
            m_creator = value;
        }
        
        const std::time_t& CPACSHeader::GetTimestamp() const
        {
            return m_timestamp;
        }
        
        void CPACSHeader::SetTimestamp(const std::time_t& value)
        {
            m_timestamp = value;
        }
        
        const std::string& CPACSHeader::GetVersion() const
        {
            return m_version;
        }
        
        void CPACSHeader::SetVersion(const std::string& value)
        {
            m_version = value;
        }
        
        const std::string& CPACSHeader::GetCpacsVersion() const
        {
            return m_cpacsVersion;
        }
        
        void CPACSHeader::SetCpacsVersion(const std::string& value)
        {
            m_cpacsVersion = value;
        }
        
        const boost::optional<CPACSUpdates>& CPACSHeader::GetUpdates() const
        {
            return m_updates;
        }
        
        boost::optional<CPACSUpdates>& CPACSHeader::GetUpdates()
        {
            return m_updates;
        }
        
    }
}
