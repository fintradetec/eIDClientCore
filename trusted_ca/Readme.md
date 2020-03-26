# Certificate Authority Keys

A certificate authority (CA) is a trusted entity that issues digital certificates, which are data files used to cryptographically link an entity with a public key.

To check validity of the certificate

      $ openssl x509 -in certificate.crt -text -noout

Example Outpub:

### CAcert.pem

      Common Name: CA Cert Signing Authority
      Organization: Root CA
      Organization Unit: http://www.cacert.org
      Valid From: March 30, 2003
      Valid To: March 29, 2033
      Issuer: CA Cert Signing Authority, Root CA
      Serial Number: 0 (0x0)
      
      
### Common Name: COMODO RSA Certification Authority

      Organization: COMODO CA Limited
      Locality: Salford
      State: Greater Manchester
      Country: GB

      1. Valid From: January 18, 2010
      Valid To: January 18, 2038
      Issuer: COMODO RSA Certification Authority, COMODO CA Limited
      Serial Number: 4caaf9cadb636fe01ff74ed85b03869d
      
      2. Valid From: February 11, 2014
      Valid To: February 11, 2029
      Issuer: COMODO RSA Certification Authority, COMODO CA Limited Write review of Sectigo
      Serial Number: 2b2e6eead975366c148a6edba37c8c07
      
