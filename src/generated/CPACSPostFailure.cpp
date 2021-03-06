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

#include "CPACSPlasticityCurvePoint.h"
#include "CPACSPostFailure.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "TixiHelper.h"

namespace tigl
{
    namespace generated
    {
        CPACSPostFailure::CPACSPostFailure() {}
        
        CPACSPostFailure::~CPACSPostFailure() {}
        
        void CPACSPostFailure::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
        {
            // read element name
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/name")) {
                m_name = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/name");
                if (m_name->empty()) {
                    LOG(WARNING) << "Optional element name is present but empty at xpath " << xpath;
                }
            }
            
            // read element description
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/description")) {
                m_description = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/description");
                if (m_description->empty()) {
                    LOG(WARNING) << "Optional element description is present but empty at xpath " << xpath;
                }
            }
            
            // read element materialLaw
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/materialLaw")) {
                m_materialLaw = tixihelper::TixiGetElement<std::string>(tixiHandle, xpath + "/materialLaw");
                if (m_materialLaw->empty()) {
                    LOG(WARNING) << "Optional element materialLaw is present but empty at xpath " << xpath;
                }
            }
            
            // read element plasticEliminationStrain
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/plasticEliminationStrain")) {
                m_plasticEliminationStrain_choice1 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/plasticEliminationStrain");
            }
            
            // read element plasticityCurvePoint
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/plasticityCurvePoint")) {
                tixihelper::TixiReadElements(tixiHandle, xpath + "/plasticityCurvePoint", m_plasticityCurvePoints_choice1);
            }
            
            // read element initialEquivalentShearStrain
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/initialEquivalentShearStrain")) {
                m_initialEquivalentShearStrain_choice2 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/initialEquivalentShearStrain");
            }
            
            // read element intermediateEquivalentShearStrain
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/intermediateEquivalentShearStrain")) {
                m_intermediateEquivalentShearStrain_choice2 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/intermediateEquivalentShearStrain");
            }
            
            // read element ultimateEquivalentShearStrain
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/ultimateEquivalentShearStrain")) {
                m_ultimateEquivalentShearStrain_choice2 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/ultimateEquivalentShearStrain");
            }
            
            // read element intermediateDamage
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/intermediateDamage")) {
                m_intermediateDamage_choice2 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/intermediateDamage");
            }
            
            // read element ultimateDamage
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/ultimateDamage")) {
                m_ultimateDamage_choice2 = tixihelper::TixiGetElement<double>(tixiHandle, xpath + "/ultimateDamage");
            }
            
            if (!ValidateChoices()) {
                LOG(ERROR) << "Invalid choice configuration at xpath " << xpath;
            }
        }
        
        void CPACSPostFailure::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
        {
            // write element name
            if (m_name) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/name");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/name", *m_name);
            } else {
                if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/name")) {
                    tixihelper::TixiRemoveElement(tixiHandle, xpath + "/name");
                }
            }
            
            // write element description
            if (m_description) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/description");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/description", *m_description);
            } else {
                if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/description")) {
                    tixihelper::TixiRemoveElement(tixiHandle, xpath + "/description");
                }
            }
            
            // write element materialLaw
            if (m_materialLaw) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/materialLaw");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/materialLaw", *m_materialLaw);
            } else {
                if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/materialLaw")) {
                    tixihelper::TixiRemoveElement(tixiHandle, xpath + "/materialLaw");
                }
            }
            
            // write element plasticEliminationStrain
            if (m_plasticEliminationStrain_choice1) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/plasticEliminationStrain");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/plasticEliminationStrain", *m_plasticEliminationStrain_choice1);
            } else {
                if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/plasticEliminationStrain")) {
                    tixihelper::TixiRemoveElement(tixiHandle, xpath + "/plasticEliminationStrain");
                }
            }
            
            // write element plasticityCurvePoint
            tixihelper::TixiSaveElements(tixiHandle, xpath + "/plasticityCurvePoint", m_plasticityCurvePoints_choice1);
            
            // write element initialEquivalentShearStrain
            if (m_initialEquivalentShearStrain_choice2) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/initialEquivalentShearStrain");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/initialEquivalentShearStrain", *m_initialEquivalentShearStrain_choice2);
            } else {
                if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/initialEquivalentShearStrain")) {
                    tixihelper::TixiRemoveElement(tixiHandle, xpath + "/initialEquivalentShearStrain");
                }
            }
            
            // write element intermediateEquivalentShearStrain
            if (m_intermediateEquivalentShearStrain_choice2) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/intermediateEquivalentShearStrain");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/intermediateEquivalentShearStrain", *m_intermediateEquivalentShearStrain_choice2);
            } else {
                if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/intermediateEquivalentShearStrain")) {
                    tixihelper::TixiRemoveElement(tixiHandle, xpath + "/intermediateEquivalentShearStrain");
                }
            }
            
            // write element ultimateEquivalentShearStrain
            if (m_ultimateEquivalentShearStrain_choice2) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/ultimateEquivalentShearStrain");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/ultimateEquivalentShearStrain", *m_ultimateEquivalentShearStrain_choice2);
            } else {
                if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/ultimateEquivalentShearStrain")) {
                    tixihelper::TixiRemoveElement(tixiHandle, xpath + "/ultimateEquivalentShearStrain");
                }
            }
            
            // write element intermediateDamage
            if (m_intermediateDamage_choice2) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/intermediateDamage");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/intermediateDamage", *m_intermediateDamage_choice2);
            } else {
                if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/intermediateDamage")) {
                    tixihelper::TixiRemoveElement(tixiHandle, xpath + "/intermediateDamage");
                }
            }
            
            // write element ultimateDamage
            if (m_ultimateDamage_choice2) {
                tixihelper::TixiCreateElementIfNotExists(tixiHandle, xpath + "/ultimateDamage");
                tixihelper::TixiSaveElement(tixiHandle, xpath + "/ultimateDamage", *m_ultimateDamage_choice2);
            } else {
                if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/ultimateDamage")) {
                    tixihelper::TixiRemoveElement(tixiHandle, xpath + "/ultimateDamage");
                }
            }
            
        }
        
        bool CPACSPostFailure::ValidateChoices() const
        {
            return
            (
                (
                    (
                        // mandatory elements of this choice must be there
                        true // m_plasticEliminationStrain_choice1 is optional in choice
                        &&
                        true // m_plasticityCurvePoints_choice1 is optional in choice
                        &&
                        // elements of other choices must not be there
                        !(
                            m_initialEquivalentShearStrain_choice2.is_initialized()
                            ||
                            m_intermediateEquivalentShearStrain_choice2.is_initialized()
                            ||
                            m_ultimateEquivalentShearStrain_choice2.is_initialized()
                            ||
                            m_intermediateDamage_choice2.is_initialized()
                            ||
                            m_ultimateDamage_choice2.is_initialized()
                        )
                    )
                    +
                    (
                        // mandatory elements of this choice must be there
                        m_initialEquivalentShearStrain_choice2.is_initialized()
                        &&
                        m_intermediateEquivalentShearStrain_choice2.is_initialized()
                        &&
                        m_ultimateEquivalentShearStrain_choice2.is_initialized()
                        &&
                        m_intermediateDamage_choice2.is_initialized()
                        &&
                        m_ultimateDamage_choice2.is_initialized()
                        &&
                        // elements of other choices must not be there
                        !(
                            m_plasticEliminationStrain_choice1.is_initialized()
                            ||
                            !m_plasticityCurvePoints_choice1.empty()
                        )
                    )
                    == 1
                )
            )
            ;
        }
        
        const boost::optional<std::string>& CPACSPostFailure::GetName() const
        {
            return m_name;
        }
        
        void CPACSPostFailure::SetName(const std::string& value)
        {
            m_name = value;
        }
        
        void CPACSPostFailure::SetName(const boost::optional<std::string>& value)
        {
            m_name = value;
        }
        
        const boost::optional<std::string>& CPACSPostFailure::GetDescription() const
        {
            return m_description;
        }
        
        void CPACSPostFailure::SetDescription(const std::string& value)
        {
            m_description = value;
        }
        
        void CPACSPostFailure::SetDescription(const boost::optional<std::string>& value)
        {
            m_description = value;
        }
        
        const boost::optional<std::string>& CPACSPostFailure::GetMaterialLaw() const
        {
            return m_materialLaw;
        }
        
        void CPACSPostFailure::SetMaterialLaw(const std::string& value)
        {
            m_materialLaw = value;
        }
        
        void CPACSPostFailure::SetMaterialLaw(const boost::optional<std::string>& value)
        {
            m_materialLaw = value;
        }
        
        const boost::optional<double>& CPACSPostFailure::GetPlasticEliminationStrain_choice1() const
        {
            return m_plasticEliminationStrain_choice1;
        }
        
        void CPACSPostFailure::SetPlasticEliminationStrain_choice1(const double& value)
        {
            m_plasticEliminationStrain_choice1 = value;
        }
        
        void CPACSPostFailure::SetPlasticEliminationStrain_choice1(const boost::optional<double>& value)
        {
            m_plasticEliminationStrain_choice1 = value;
        }
        
        const std::vector<unique_ptr<CPACSPlasticityCurvePoint> >& CPACSPostFailure::GetPlasticityCurvePoints_choice1() const
        {
            return m_plasticityCurvePoints_choice1;
        }
        
        std::vector<unique_ptr<CPACSPlasticityCurvePoint> >& CPACSPostFailure::GetPlasticityCurvePoints_choice1()
        {
            return m_plasticityCurvePoints_choice1;
        }
        
        const boost::optional<double>& CPACSPostFailure::GetInitialEquivalentShearStrain_choice2() const
        {
            return m_initialEquivalentShearStrain_choice2;
        }
        
        void CPACSPostFailure::SetInitialEquivalentShearStrain_choice2(const double& value)
        {
            m_initialEquivalentShearStrain_choice2 = value;
        }
        
        void CPACSPostFailure::SetInitialEquivalentShearStrain_choice2(const boost::optional<double>& value)
        {
            m_initialEquivalentShearStrain_choice2 = value;
        }
        
        const boost::optional<double>& CPACSPostFailure::GetIntermediateEquivalentShearStrain_choice2() const
        {
            return m_intermediateEquivalentShearStrain_choice2;
        }
        
        void CPACSPostFailure::SetIntermediateEquivalentShearStrain_choice2(const double& value)
        {
            m_intermediateEquivalentShearStrain_choice2 = value;
        }
        
        void CPACSPostFailure::SetIntermediateEquivalentShearStrain_choice2(const boost::optional<double>& value)
        {
            m_intermediateEquivalentShearStrain_choice2 = value;
        }
        
        const boost::optional<double>& CPACSPostFailure::GetUltimateEquivalentShearStrain_choice2() const
        {
            return m_ultimateEquivalentShearStrain_choice2;
        }
        
        void CPACSPostFailure::SetUltimateEquivalentShearStrain_choice2(const double& value)
        {
            m_ultimateEquivalentShearStrain_choice2 = value;
        }
        
        void CPACSPostFailure::SetUltimateEquivalentShearStrain_choice2(const boost::optional<double>& value)
        {
            m_ultimateEquivalentShearStrain_choice2 = value;
        }
        
        const boost::optional<double>& CPACSPostFailure::GetIntermediateDamage_choice2() const
        {
            return m_intermediateDamage_choice2;
        }
        
        void CPACSPostFailure::SetIntermediateDamage_choice2(const double& value)
        {
            m_intermediateDamage_choice2 = value;
        }
        
        void CPACSPostFailure::SetIntermediateDamage_choice2(const boost::optional<double>& value)
        {
            m_intermediateDamage_choice2 = value;
        }
        
        const boost::optional<double>& CPACSPostFailure::GetUltimateDamage_choice2() const
        {
            return m_ultimateDamage_choice2;
        }
        
        void CPACSPostFailure::SetUltimateDamage_choice2(const double& value)
        {
            m_ultimateDamage_choice2 = value;
        }
        
        void CPACSPostFailure::SetUltimateDamage_choice2(const boost::optional<double>& value)
        {
            m_ultimateDamage_choice2 = value;
        }
        
    }
}
