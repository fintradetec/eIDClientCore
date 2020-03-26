# Certificate Authority Keys

A certificate authority (CA) is a trusted entity that issues digital certificates, which are data files used to cryptographically link an entity with a public key.

To check validity of the certificate

      $ openssl x509 -in certificate.crt -text -noout
