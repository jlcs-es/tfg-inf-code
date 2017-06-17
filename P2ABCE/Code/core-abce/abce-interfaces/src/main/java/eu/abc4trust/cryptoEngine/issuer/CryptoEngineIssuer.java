//* Licensed Materials - Property of                                  *
//* IBM                                                               *
//* Miracle A/S                                                       *
//* Alexandra Instituttet A/S                                         *
//*                                                                   *
//* eu.abc4trust.pabce.1.34                                           *
//*                                                                   *
//* (C) Copyright IBM Corp. 2014. All Rights Reserved.                *
//* (C) Copyright Miracle A/S, Denmark. 2014. All Rights Reserved.    *
//* (C) Copyright Alexandra Instituttet A/S, Denmark. 2014. All       *
//* Rights Reserved.                                                  *
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

// * Licensed Materials - Property of IBM, Miracle A/S, and *
// * Alexandra Instituttet A/S *
// * eu.abc4trust.pabce.1.0 *
// * (C) Copyright IBM Corp. 2012. All Rights Reserved. *
// * (C) Copyright Miracle A/S, Denmark. 2012. All Rights Reserved. *
// * (C) Copyright Alexandra Instituttet A/S, Denmark. 2012. All *
// * Rights Reserved. *
// * US Government Users Restricted Rights - Use, duplication or *
// * disclosure restricted by GSA ADP Schedule Contract with IBM Corp. *
// */**/****************************************************************

package eu.abc4trust.cryptoEngine.issuer;

import java.net.URI;
import java.util.List;

import eu.abc4trust.cryptoEngine.CryptoEngineException;
import eu.abc4trust.returnTypes.IssuerParametersAndSecretKey;
import eu.abc4trust.xml.Attribute;
import eu.abc4trust.xml.FriendlyDescription;
import eu.abc4trust.xml.IssuanceLogEntry;
import eu.abc4trust.xml.IssuanceMessage;
import eu.abc4trust.xml.IssuanceMessageAndBoolean;
import eu.abc4trust.xml.IssuancePolicy;
import eu.abc4trust.xml.IssuanceTokenAndIssuancePolicy;
import eu.abc4trust.xml.IssuanceTokenDescription;
import eu.abc4trust.xml.SystemParameters;

public interface CryptoEngineIssuer {

  /**
   * This method is invoked on an issuance policy (possibly containing only a credential
   * specificationUIDin case of an issuance from scratch), known attributes atts and a context
   * string. It invokes the mechanism-specific cryptographic routines for the first step in an
   * interactive issuance protocol and stores its cryptographic state in a temporary storage
   * associated to the context. It finally returns an outgoing issuance message with the same
   * context attribute ctxt, plus a boolean indicating whether this is the last flow of the issuance
   * protocol. If the credential to be issued is subject to Issuer-driven revocation, then,
   * depending on the revocation mechanism, the CryptoEngine may have to interact with the
   * Revocation Authority. If so, then it prepares a mechanism-specific Revocation Message m and
   * calling RevocationProxy.processRevocationMessage(m, revpars).
   * 
   * @param ip
   * @param atts
   * @param ctxt
   * @return
   * @throws CryptoEngineException
   */
  public IssuanceMessageAndBoolean initIssuanceProtocol(IssuancePolicy ip, List<Attribute> atts,
      URI ctxt) throws CryptoEngineException;

  /**
   * On input an incoming issuance message m, this method first extracts the context attribute and
   * obtains the cryptographic state information that is stored under the same context value. It
   * then invokes the mechanism-specific cryptographic routines for one step in an interactive
   * issuance protocol and returns an outgoing issuance message. The method eventually also stores
   * new cryptographic state information associated to the context attribute, and attaches the
   * context attribute to the outgoing message. The returned boolean indicates whether this is the
   * last flow of the issuance protocol. If so, the method deletes all temporary state information.
   * If the credential to be issued is subject to Issuer-driven revocation, then, depending on the
   * revocation mechanism, the CryptoEngine may have to interact with the Revocation Authority. If
   * so, then it prepares a mechanism-specific Revocation Message m and calling
   * RevocationProxy.processRevocationMessage(m, revpars).
   * 
   * This method also verifies that the cryptographic evidence contained within the issuance message
   * (for example an issuance token) are correct. For issuance tokens this method will particularly
   * check whether the requirements concerning the carried-over and (jointly)-random attributes are
   * met. In order to verify the token, this method may call upon the KeyManager to obtain Issuer
   * parameters, Inspector public keys, Revocation Authority parameters, and the current revocation
   * information. If the evidence is deemed invalid, this method will throw a RuntimeException.
   * 
   * @param m
   * @return
   * @throws CryptoEngineException
   */
  public IssuanceMessageAndBoolean issuanceProtocolStep(IssuanceMessage m)
      throws CryptoEngineException;

  /**
   * This method generates a fresh set of system parameters for the given key length and
   * cryptographic mechanism. Issuers can generate their own system parameters, but can also reuse
   * system parameters generated by a different entity.
   * 
   * @param keyLength
   * @param cryptographicMechanism
   * @return
   * @throws CryptoEngineException
   */
  public SystemParameters setupSystemParameters(int keyLength) throws CryptoEngineException;

  /**
   * This method generates and returns a fresh issuance key and the corresponding Issuer parameters.
   * The input to this method specify the credential specification credspec of the credentials that
   * will be issued with these parameters, the system parameters syspars, the unique identifier uid
   * of the generated parameters, the hash algorithm identifier hash, and, optionally, the
   * parameters identifier for any Issuer-driven Revocation Authority.
   * 
   * @param credspec
   * @param syspars
   * @param uid
   * @param hash
   * @param revParsUid
   * @return
   * @throws CryptoEngineException
   */
  public IssuerParametersAndSecretKey setupIssuerParameters(SystemParameters syspars,
      int maximalNumberOfAttributes, URI technology, URI uid, URI revocationAuthority,
      List<FriendlyDescription> friendlyIssuerDescription) throws CryptoEngineException;

  /**
   * This method looks up an issuance log entry of previously issued credentials that contains a
   * verified issuance token together with the attribute values provided by the issuer. The issuance
   * log entry identifier issuanceEntryUid is the identifier that was included in the issuance token
   * description that was returned when the token was verified.
   */
  IssuanceLogEntry getIssuanceLogEntry(URI issuanceEntryUid) throws CryptoEngineException;

  /**
   * This method looks for an IssuanceTokenDescription inside the issuance message. This method
   * returns the issuance token, or NULL if none could be found. It is guaranteed that this method
   * returns a non-null value before a new credential is actually issued, so that the upper layers
   * may abort the issuance protocol if a certain condition is not satisfied (such as the absence of
   * a registered pseudonym).
   */
  public IssuanceTokenDescription extractIssuanceTokenDescription(IssuanceMessage issuanceMessage);

  /**
   * If the given issuance message contains an issuance token, this method returns said issuance
   * token together with the issuance policy this issuer was initialized with. Otherwise return
   * null. If this method returns non-null, the caller is expected to check the issuance token
   * against the issuance policy. It is mandatory to call this method before each call to
   * issuanceStep (otherwise the issuer will fail during verification of the issuance token).
   * 
   * @param issuanceMessage
   * @return
   * @throws IssuanceOrchestrationException
   */
  public IssuanceTokenAndIssuancePolicy extractIssuanceTokenAndPolicy(
      IssuanceMessage issuanceMessage) throws CryptoEngineException;

}