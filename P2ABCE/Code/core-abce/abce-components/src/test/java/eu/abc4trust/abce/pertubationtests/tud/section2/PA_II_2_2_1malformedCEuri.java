//* Licensed Materials - Property of                                  *
//* IBM                                                               *
//* Alexandra Instituttet A/S                                         *
//*                                                                   *
//* eu.abc4trust.pabce.1.34                                           *
//*                                                                   *
//* (C) Copyright IBM Corp. 2014. All Rights Reserved.                *
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

package eu.abc4trust.abce.pertubationtests.tud.section2;


import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

import java.io.IOException;
import java.io.InputStream;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;
import java.util.logging.FileHandler;
import java.util.logging.Handler;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.logging.SimpleFormatter;

import org.apache.commons.lang.RandomStringUtils;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import com.google.inject.Guice;
import com.google.inject.Injector;

import eu.abc4trust.abce.external.issuer.IssuerAbcEngine;
import eu.abc4trust.abce.external.user.UserAbcEngine;
import eu.abc4trust.abce.external.verifier.VerifierAbcEngine;
import eu.abc4trust.abce.testharness.IntegrationModuleFactory;
import eu.abc4trust.abce.testharness.IssuanceHelper;
import eu.abc4trust.abce.testharness.PolicySelector;
import eu.abc4trust.cryptoEngine.util.SystemParametersUtil;
import eu.abc4trust.keyManager.KeyManager;
import eu.abc4trust.revocationProxy.revauth.RevocationProxyAuthority;
import eu.abc4trust.util.CryptoUriUtil;
import eu.abc4trust.xml.CredentialDescription;
import eu.abc4trust.xml.CredentialSpecification;
import eu.abc4trust.xml.IssuancePolicy;
import eu.abc4trust.xml.IssuerParameters;
import eu.abc4trust.xml.PresentationPolicyAlternatives;
import eu.abc4trust.xml.PresentationToken;
import eu.abc4trust.xml.PresentationTokenDescription;
import eu.abc4trust.xml.SystemParameters;
import eu.abc4trust.xml.util.XmlUtils;


/**
 * Pertubation tests 2.2.1, 
 */
public class PA_II_2_2_1malformedCEuri {

    private static final String CREDENTIAL_SPECIFICATION_ID_CARD = "/eu/abc4trust/sampleXml/credspecs/credentialSpecificationSimpleIdentitycard.xml";
    private static final String ISSUANCE_POLICY_ID_CARD = "/eu/abc4trust/sampleXml/issuance/issuancePolicySimpleIdentitycard.xml";
    private static final String PRESENTATION_POLICY_ID_CARD = "/eu/abc4trust/sampleXml/presentationPolicies/presentationPolicySimpleIdentitycard.xml";
    private static final String USERNAME = "defaultUser";
    
    private static final Logger logger = java.util.logging.Logger.getLogger("PA Section 2.2.1 bit malformed ce uri");
   // private ObjectFactory of = new ObjectFactory();

    
	private URI uid = null;
	private URI revParsUid = null;
	private URI hash = null;
	private URI algorithmId = null;
	private Injector userInjector = null;
	private Injector issuerInjector = null;
	private Injector verifierInjector = null;
	private CredentialSpecification idcardCredSpec = null;

	private IssuerAbcEngine issuerEngine = null;

	private String testName="none";
	
	@BeforeClass
	public static void setupLogger() throws SecurityException, IOException {
		Handler fh = new FileHandler("PA-Section-2.2.1-malformedCE.log");
		SimpleFormatter simpleFormatter = new SimpleFormatter();
		fh.setFormatter(simpleFormatter);
		logger.addHandler(fh);
	}
	
	@Before
	public void setup() throws Exception {
		uid = URI.create("http://my.country/identitycard/issuancekey_v1.0");
		revParsUid = URI.create("urn:revocation:uid");
		hash = URI.create("urn:abc4trust:1.0:hashalgorithm:sha-256");
		algorithmId = CryptoUriUtil.getIdemixMechanism();

        userInjector = Guice.createInjector(IntegrationModuleFactory.newModule(
                new Random(1987)));

        verifierInjector = Guice
                .createInjector(IntegrationModuleFactory.newModule(new Random(1231))); 

		idcardCredSpec = (CredentialSpecification) XmlUtils
	                .getObjectFromXML(
	                        this.getClass().getResourceAsStream(
	                                CREDENTIAL_SPECIFICATION_ID_CARD), true);
		
		userInjector.getInstance(KeyManager.class).storeCredentialSpecification(
	            idcardCredSpec.getSpecificationUID(), idcardCredSpec);

		verifierInjector.getInstance(KeyManager.class).storeCredentialSpecification(
	            idcardCredSpec.getSpecificationUID(), idcardCredSpec);
        
        
	}
	
	
	public void runTest(int key, URI engineURI) throws Exception{
		logger.info(testName+"  PA Flow: Running test with security parameter: "
				+key
				+" and engine URI: "+engineURI.toString());
		
		SystemParameters sysParams = null;
		IssuerParameters ip = null;
		boolean testSuccess=false;
		logger.info("	Trying to create system parameters");
		try{
    		Injector revocationInjector = Guice
    			.createInjector(IntegrationModuleFactory.newModule(new Random(1231)));
    
    		RevocationProxyAuthority revocationProxyAuthority = revocationInjector
    				.getInstance(RevocationProxyAuthority.class);
    	
    		issuerInjector = Guice
    				.createInjector(IntegrationModuleFactory.newModule(new Random(1231), revocationProxyAuthority));
        
    		issuerEngine = issuerInjector
    				.getInstance(IssuerAbcEngine.class);

    		sysParams = SystemParametersUtil.getDefaultSystemParameters_1024();
			
			issuerInjector.getInstance(KeyManager.class).storeSystemParameters(sysParams);
			userInjector.getInstance(KeyManager.class).storeSystemParameters(sysParams);
			verifierInjector.getInstance(KeyManager.class).storeSystemParameters(sysParams);
		}catch(Exception e){
			logger.log(Level.SEVERE,"	Failed to create SystemParameters : "
					+e.getMessage()+"\n				StackTreacs: "+Arrays.toString(e.getStackTrace()));
			testSuccess=true;
		}
		
		if(!testSuccess){//No failure so far
			if(sysParams==null){
				logger.info("TEST FAIL !!! System parameters NULL!!! NO EXCEPTION !!! TEST FAIL !!!");
				testSuccess=false;
				assertTrue(false);
			} else {
				logger.info("	System parameters created successfully");
				logger.info("	Trying to create IssuerParameters");
				try{
					ip = issuerEngine
							.setupIssuerParameters(idcardCredSpec, sysParams, uid, hash, algorithmId, revParsUid, null);
				}catch(Exception e){
					logger.log(Level.SEVERE,"	Failed to create IssuerParameters: "
							+e.getMessage()+ "\n				 StackTrace: "+Arrays.toString(e.getStackTrace()));
					testSuccess=true;
				}
			}
		}	
		
		if(!testSuccess){//No failure so far
			if(ip==null){
				logger.info("TEST FAIL !!!	Issuer parameters NULL!!!  NO EXCEPTION !!! TEST FAIL !!!");
				testSuccess=false;
				assertTrue(false);
			} else {
				logger.info("	Issuer parameters created successfully");
			}
		}
		
		
		if(!testSuccess){//No failure so far
			boolean idCardIssued=true;
			if(!testSuccess){//No failure so far 
				logger.info("	Trying to issue ID Card");
				
				try{
					issueIDCard(ip);
						logger.info("Used IssuerParameters to issue a credential");
				}catch (Exception e){
					logger.log(Level.SEVERE,"	Failed to issue credential : "
							+e.getMessage()+ "\n StackTrace: "+Arrays.toString(e.getStackTrace()));
					idCardIssued=false;
				}
			}
			if(idCardIssued){//Immediate test failure
				logger.info("PA FLOW TEST FAIL !!! ID CARD ISSUED USING PERTUBATED DATA!!! TEST FAIL !!!");
				assertTrue(false);
			}
			
			
			boolean presentIDCard=true;
			if(!testSuccess){//No failure so far
				logger.info("	Trying to issue Presentation Token");
				PresentationToken pt = null;
				try{
					pt = createPresentationToken();
		    	}catch(Exception e){
		    		logger.log(Level.SEVERE,"Failed to create presentation token : "
		    				+e.getMessage()+ "\n StackTrace: "+Arrays.toString(e.getStackTrace()));
		    		presentIDCard=false;
		    	}
				
				if(presentIDCard){//token created without exception
					if(pt == null){// token not created, no exception => test fail
						logger.info("PA FLOW TEST FAIL !!!	Presentation Token NULL!!! NO EXCEPTION !!! TEST FAIL !!!");
						assertTrue(false);
					}
					logger.info("	Presentation Token Created");
					logger.info("	Trying to Verify Presentation Token");
					PresentationTokenDescription ptd = null;
					try{	
			    		ptd = verifyPresentationToken(pt);
			    	}catch(Exception e){
			    		logger.log(Level.SEVERE,"Failed to verify presentation token : "
			    				+e.getMessage()+ "\n StackTrace: "+Arrays.toString(e.getStackTrace()));
			    		presentIDCard=false;
			    	}
					if(presentIDCard){//token description created without exception
						if(ptd == null){// token description not created, no exception => test fail
							logger.info("PA FLOW TEST FAIL !!!	Presentation Token Description NULL!!! NO EXCEPTION !!! TEST FAIL !!!");
							assertTrue(false);
						}
						logger.info("	Succesfully verified presentation token");
					}
				}
			}
			
			if(presentIDCard){//Immediate test failure
				logger.info("PA FLOW TEST FAIL !!! PRESENTATION TOKEN FOR ID CARD CREATED AND VERIFIED USING PERTUBATED DATA!!! TEST FAIL !!!");
				assertTrue(false);
			}
			
			if(!presentIDCard && !idCardIssued){
				testSuccess=true;
				logger.info("Failed to issue Id card and create presentation token");
				
			}
		}	
		
		//Test evaluation
		if(!testSuccess){
			logger.info("PA FLOW TEST FAIL !!! NO EXCEPTION !!! TEST FAIL !!!");
			assertTrue(false);
		} else {
			logger.info("PA FLOW TEST SUCCESSFULL !!!  EXCEPTION HANDLED !!! TEST SUCCESSFULL  !!!");
			assertTrue(true);
		}
		
		
	}
	

// TUD test	
	public static URI randomURI() throws URISyntaxException{//generates a random URI
		//urn:abc4trust:1.0:algorithm:idemix
		String uriString="urn:";
		uriString+=RandomStringUtils.randomAlphanumeric(5)+":";
		uriString+=RandomStringUtils.randomAlphanumeric(10)+":";
		uriString+=RandomStringUtils.randomAlphanumeric(10)+":";	
		uriString+=RandomStringUtils.randomAlphanumeric(10);	
		
		URI randomUri = new URI(uriString);
		return randomUri;
	}
	
	@Test
    public void engineURIrandomTest() throws Exception {// runs the test 10 times with a random URI
		testName="engineURIrandom";
		
		for(int i=1; i<= 10; i++)
			runTest(128, randomURI());
		
    }
	
// end of TUD test		
	
	
	private void issueIDCard(IssuerParameters ip) throws Exception{
        KeyManager userKeyManager = userInjector.getInstance(KeyManager.class);
        KeyManager issuerKeyManager = issuerInjector.getInstance(KeyManager.class);
        KeyManager verifierKeyManager = verifierInjector.getInstance(KeyManager.class);
        
        IssuancePolicy idcardIssuancePolicy = (IssuancePolicy) XmlUtils
                .getObjectFromXML(
                        this.getClass().getResourceAsStream(
                                ISSUANCE_POLICY_ID_CARD), true);
        URI idcardIssuancePolicyUid = idcardIssuancePolicy
                .getCredentialTemplate().getIssuerParametersUID();

        
        userKeyManager.storeIssuerParameters(idcardIssuancePolicyUid,
                ip);
        issuerKeyManager.storeIssuerParameters(idcardIssuancePolicyUid,
                ip);
        verifierKeyManager.storeIssuerParameters(idcardIssuancePolicyUid,
                ip);
        
        IssuanceHelper issuanceHelper = new IssuanceHelper();
        
        	issueAndStoreIdcard(issuerInjector, userInjector, issuanceHelper, CREDENTIAL_SPECIFICATION_ID_CARD);
	}
	
	
    private void issueAndStoreIdcard(Injector issuerInjector,
            Injector userInjector, IssuanceHelper issuanceHelper, String credSpec)
                    throws Exception {
        
        Map<String, Object> att = new HashMap<String, Object>();
        att.put("FirstName", "NAME");
        att.put("LastName", "LASTNAME");
        att.put("Birthday", "1990-02-06Z");
        CredentialDescription cd = issuanceHelper.issueCredential(USERNAME, issuerInjector, userInjector,
                credSpec, ISSUANCE_POLICY_ID_CARD,
                att);
        assertNotNull(cd);
    }
    private PresentationToken createPresentationToken() throws Exception{
    	UserAbcEngine userEngine = userInjector
                .getInstance(UserAbcEngine.class);
       	InputStream resourceAsStream = this.getClass().getResourceAsStream(
                PRESENTATION_POLICY_ID_CARD);
    	PresentationPolicyAlternatives presentationPolicyAlternatives = (PresentationPolicyAlternatives) XmlUtils
                .getObjectFromXML(
                        resourceAsStream, true);
    	
    	PresentationToken pt = null;
    	
    	pt = userEngine.createPresentationTokenFirstChoice(USERNAME, presentationPolicyAlternatives);
    	
    	return pt;
    }
    
    private PresentationTokenDescription verifyPresentationToken(PresentationToken pt) throws Exception{
    	VerifierAbcEngine verifierEngine = verifierInjector
                .getInstance(VerifierAbcEngine.class);
       	InputStream resourceAsStream = this.getClass().getResourceAsStream(
                PRESENTATION_POLICY_ID_CARD);
    	PresentationPolicyAlternatives presentationPolicyAlternatives = (PresentationPolicyAlternatives) XmlUtils
                .getObjectFromXML(
                        resourceAsStream, true);
    	PresentationTokenDescription ptd = verifierEngine.verifyTokenAgainstPolicy(presentationPolicyAlternatives, pt, false);
    	return ptd;
		
    }
    
}