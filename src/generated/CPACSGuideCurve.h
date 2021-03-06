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
#include <string>
#include <tixi.h>
#include "CPACSGuideCurve_continuity.h"
#include "CPACSPointXYZ.h"
#include "tigl_internal.h"

namespace tigl
{
    class CTiglUIDManager;
    
    namespace generated
    {
        // This class is used in:
        // CPACSGuideCurves
        
        // generated from /xsd:schema/xsd:complexType[421]
        class CPACSGuideCurve
        {
        public:
            TIGL_EXPORT CPACSGuideCurve(CTiglUIDManager* uidMgr);
            TIGL_EXPORT virtual ~CPACSGuideCurve();
            
            TIGL_EXPORT CTiglUIDManager& GetUIDManager();
            TIGL_EXPORT const CTiglUIDManager& GetUIDManager() const;
            
            TIGL_EXPORT virtual void ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath);
            TIGL_EXPORT virtual void WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const;
            
            TIGL_EXPORT bool ValidateChoices() const;
            
            TIGL_EXPORT virtual const std::string& GetUID() const;
            TIGL_EXPORT virtual void SetUID(const std::string& value);
            
            TIGL_EXPORT virtual const std::string& GetName() const;
            TIGL_EXPORT virtual void SetName(const std::string& value);
            
            TIGL_EXPORT virtual const boost::optional<std::string>& GetDescription() const;
            TIGL_EXPORT virtual void SetDescription(const std::string& value);
            TIGL_EXPORT virtual void SetDescription(const boost::optional<std::string>& value);
            
            TIGL_EXPORT virtual const std::string& GetGuideCurveProfileUID() const;
            TIGL_EXPORT virtual void SetGuideCurveProfileUID(const std::string& value);
            
            TIGL_EXPORT virtual const boost::optional<std::string>& GetFromGuideCurveUID_choice1() const;
            TIGL_EXPORT virtual void SetFromGuideCurveUID_choice1(const std::string& value);
            TIGL_EXPORT virtual void SetFromGuideCurveUID_choice1(const boost::optional<std::string>& value);
            
            TIGL_EXPORT virtual const boost::optional<CPACSGuideCurve_continuity>& GetContinuity_choice1() const;
            TIGL_EXPORT virtual void SetContinuity_choice1(const CPACSGuideCurve_continuity& value);
            TIGL_EXPORT virtual void SetContinuity_choice1(const boost::optional<CPACSGuideCurve_continuity>& value);
            
            TIGL_EXPORT virtual const boost::optional<double>& GetFromRelativeCircumference_choice2() const;
            TIGL_EXPORT virtual void SetFromRelativeCircumference_choice2(const double& value);
            TIGL_EXPORT virtual void SetFromRelativeCircumference_choice2(const boost::optional<double>& value);
            
            TIGL_EXPORT virtual const boost::optional<CPACSPointXYZ>& GetTangent_choice2() const;
            TIGL_EXPORT virtual boost::optional<CPACSPointXYZ>& GetTangent_choice2();
            
            TIGL_EXPORT virtual const double& GetToRelativeCircumference() const;
            TIGL_EXPORT virtual void SetToRelativeCircumference(const double& value);
            
            TIGL_EXPORT virtual const boost::optional<CPACSPointXYZ>& GetTangent() const;
            TIGL_EXPORT virtual boost::optional<CPACSPointXYZ>& GetTangent();
            
        protected:
            CTiglUIDManager* m_uidMgr;
            
            std::string                                 m_uID;
            std::string                                 m_name;
            boost::optional<std::string>                m_description;
            std::string                                 m_guideCurveProfileUID;
            boost::optional<std::string>                m_fromGuideCurveUID_choice1;
            boost::optional<CPACSGuideCurve_continuity> m_continuity_choice1;
            boost::optional<double>                     m_fromRelativeCircumference_choice2;
            boost::optional<CPACSPointXYZ>              m_tangent_choice2;
            double                                      m_toRelativeCircumference;
            boost::optional<CPACSPointXYZ>              m_tangent;
            
        private:
            #ifdef HAVE_CPP11
            CPACSGuideCurve(const CPACSGuideCurve&) = delete;
            CPACSGuideCurve& operator=(const CPACSGuideCurve&) = delete;
            
            CPACSGuideCurve(CPACSGuideCurve&&) = delete;
            CPACSGuideCurve& operator=(CPACSGuideCurve&&) = delete;
            #else
            CPACSGuideCurve(const CPACSGuideCurve&);
            CPACSGuideCurve& operator=(const CPACSGuideCurve&);
            #endif
        };
    }
    
    // Aliases in tigl namespace
    #ifdef HAVE_CPP11
    using CCPACSGuideCurve = generated::CPACSGuideCurve;
    #else
    typedef generated::CPACSGuideCurve CCPACSGuideCurve;
    #endif
}
