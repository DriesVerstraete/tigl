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
#include <CCPACSPoint.h>
#include <CCPACSPointAbsRel.h>
#include <string>
#include <tixi.h>
#include <typeinfo>
#include "CTiglError.h"
#include "tigl_internal.h"

namespace tigl
{
    class CTiglUIDManager;
    
    namespace generated
    {
        // This class is used in:
        // CPACSFuselage
        // CPACSFuselageElement
        // CPACSFuselageSection
        // CPACSGenericGeometricComponent
        // CPACSRotor
        // CPACSRotorHubHinge
        // CPACSWing
        // CPACSWingElement
        // CPACSWingSection
        
        // generated from /xsd:schema/xsd:complexType[848]
        class CPACSTransformation
        {
        public:
            TIGL_EXPORT CPACSTransformation(CTiglUIDManager* uidMgr);
            TIGL_EXPORT virtual ~CPACSTransformation();
            
            TIGL_EXPORT CTiglUIDManager& GetUIDManager();
            TIGL_EXPORT const CTiglUIDManager& GetUIDManager() const;
            
            TIGL_EXPORT virtual void ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath);
            TIGL_EXPORT virtual void WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const;
            
            TIGL_EXPORT virtual const boost::optional<std::string>& GetUID() const;
            TIGL_EXPORT virtual void SetUID(const std::string& value);
            TIGL_EXPORT virtual void SetUID(const boost::optional<std::string>& value);
            
            TIGL_EXPORT virtual const boost::optional<CCPACSPoint>& GetScaling() const;
            TIGL_EXPORT virtual boost::optional<CCPACSPoint>& GetScaling();
            
            TIGL_EXPORT virtual const boost::optional<CCPACSPoint>& GetRotation() const;
            TIGL_EXPORT virtual boost::optional<CCPACSPoint>& GetRotation();
            
            TIGL_EXPORT virtual const boost::optional<CCPACSPointAbsRel>& GetTranslation() const;
            TIGL_EXPORT virtual boost::optional<CCPACSPointAbsRel>& GetTranslation();
            
        protected:
            CTiglUIDManager* m_uidMgr;
            
            boost::optional<std::string>       m_uID;
            boost::optional<CCPACSPoint>       m_scaling;
            boost::optional<CCPACSPoint>       m_rotation;
            boost::optional<CCPACSPointAbsRel> m_translation;
            
        private:
            #ifdef HAVE_CPP11
            CPACSTransformation(const CPACSTransformation&) = delete;
            CPACSTransformation& operator=(const CPACSTransformation&) = delete;
            
            CPACSTransformation(CPACSTransformation&&) = delete;
            CPACSTransformation& operator=(CPACSTransformation&&) = delete;
            #else
            CPACSTransformation(const CPACSTransformation&);
            CPACSTransformation& operator=(const CPACSTransformation&);
            #endif
        };
    }
    
    // CPACSTransformation is customized, use type CCPACSTransformation directly
}
