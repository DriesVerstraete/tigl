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

#pragma once

#include <boost/optional.hpp>
#include <boost/utility/in_place_factory.hpp>
#include <CCPACSWingCells.h>
#include <string>
#include <tixi.h>
#include "CPACSWingSkin.h"
#include "tigl_internal.h"

namespace tigl
{
    class CTiglUIDManager;
    class CCPACSWingCSStructure;
    
    namespace generated
    {
        // This class is used in:
        // CPACSWingComponentSegmentStructure
        
        // generated from /xsd:schema/xsd:complexType[924]
        class CPACSWingShell
        {
        public:
            TIGL_EXPORT CPACSWingShell(CCPACSWingCSStructure* parent, CTiglUIDManager* uidMgr);
            
            TIGL_EXPORT virtual ~CPACSWingShell();
            
            TIGL_EXPORT CCPACSWingCSStructure* GetParent() const;
            
            TIGL_EXPORT CTiglUIDManager& GetUIDManager();
            TIGL_EXPORT const CTiglUIDManager& GetUIDManager() const;
            
            TIGL_EXPORT virtual void ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath);
            TIGL_EXPORT virtual void WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const;
            
            TIGL_EXPORT virtual const boost::optional<std::string>& GetUID() const;
            TIGL_EXPORT virtual void SetUID(const std::string& value);
            TIGL_EXPORT virtual void SetUID(const boost::optional<std::string>& value);
            
            TIGL_EXPORT virtual const CPACSWingSkin& GetSkin() const;
            TIGL_EXPORT virtual CPACSWingSkin& GetSkin();
            
            TIGL_EXPORT virtual const boost::optional<CCPACSWingCells>& GetCells() const;
            TIGL_EXPORT virtual boost::optional<CCPACSWingCells>& GetCells();
            
        protected:
            CCPACSWingCSStructure* m_parent;
            
            CTiglUIDManager* m_uidMgr;
            
            boost::optional<std::string>     m_uID;
            CPACSWingSkin                    m_skin;
            boost::optional<CCPACSWingCells> m_cells;
            
        private:
            #ifdef HAVE_CPP11
            CPACSWingShell(const CPACSWingShell&) = delete;
            CPACSWingShell& operator=(const CPACSWingShell&) = delete;
            
            CPACSWingShell(CPACSWingShell&&) = delete;
            CPACSWingShell& operator=(CPACSWingShell&&) = delete;
            #else
            CPACSWingShell(const CPACSWingShell&);
            CPACSWingShell& operator=(const CPACSWingShell&);
            #endif
        };
    }
    
    // CPACSWingShell is customized, use type CCPACSWingShell directly
}
