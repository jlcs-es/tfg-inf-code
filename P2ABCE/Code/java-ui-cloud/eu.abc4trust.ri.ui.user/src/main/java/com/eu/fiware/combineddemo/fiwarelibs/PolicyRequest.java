//* Licensed Materials - Property of                                  *
//* IBM                                                               *
//* Nokia                                                             *
//*                                                                   *
//* eu.abc4trust.pabce.1.34                                           *
//*                                                                   *
//* (C) Copyright IBM Corp. 2015. All Rights Reserved.                *
//* (C) Copyright Nokia. 2015. All Rights Reserved.                   *
//* US Government Users Restricted Rights - Use, duplication or       *
//* disclosure restricted by GSA ADP Schedule Contract with IBM Corp. *
//*                                                                   *
//* This file is licensed under the Apache License, Version 2.0 (the  *
//* "License"); you may not use this file except in compliance with   *
//* the License. You may obtain a copy of the License at:             *
//*   http://www.apache.org/licenses/LICENSE-2.0                      *
//* Unless required by applicable law or agreed to in writing,        *
//* software distributed under the License is distributed on an       *
//* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY            *
//* KIND, either express or implied.  See the License for the         *
//* specific language governing permissions and limitations           *
//* under the License.                                                *
//*/**/****************************************************************

package com.eu.fiware.combineddemo.fiwarelibs;

import java.io.Serializable;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;

@XmlRootElement(name = "PolicyRequest")
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "PolicyRequest", propOrder = {
    "verifierName",
    "verifierPassword",
    "policyID"
})


public class PolicyRequest implements Serializable{
    
    private static final long serialVersionUID = 6220183326017714466L;
    
    @XmlElement (name = "VerifierName")
    protected String verifierName;
    
    @XmlElement (name = "VerifierPassword")
    protected String verifierPassword;
    
    @XmlElement (name = "PolicyID")
    protected String policyID;

    /**
     * Gets the value of the Username property.
     *
     * @return possible object is {@link String }
     *
     */
    
    public String getVerifierName() {
        System.out.println("Version 2.0 of PolicyRequest");
        return this.verifierName;
    }

    /**
     * Sets the value of the Username property.
     *
     * @param value allowed object is {@link String }
     *
     */
    public void setVerifierName(String value) {
        System.out.println("Version 2.0 of PolicyRequest");
        this.verifierName = value;
    }

    /**
     * Gets the value of the Password property.
     *
     * @return possible object is {@link String }
     *
     */
    
    public String getVerifierPassword() {
        return this.verifierPassword;
    }

    /**
     * Sets the value of the Password property.
     *
     * @param value allowed object is {@link String }
     *
     */
    public void setVerifierPassword(String value) {
        this.verifierPassword = value;
    }

    /**
     * Gets the value of the PolicyID property.
     *
     * @return possible object is {@link String }
     *
     */
    
    public String getPolicyID() {
        return this.policyID;
    }

    /**
     * Sets the value of the PolicyID property.
     *
     * @param value allowed object is {@link String }
     *
     */
    public void setPolicyID(String value) {
        this.policyID = value;
    }

}
