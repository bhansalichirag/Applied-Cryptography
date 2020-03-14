import requests

from cryptography.hazmat.primitives.serialization.pkcs12 import load_key_and_certificates
from cryptography.hazmat.primitives.serialization import Encoding, PrivateFormat, NoEncryption
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import serialization
from OpenSSL import crypto
from cryptography import x509
#from requests_toolbelt.adapters.x509 import X509Adapter

# backend = default_backend()
# # with open('C:\\Users\\bhans\\Downloads\\Fall 2019\\Crypto\\Project5\\Certificates\\cert_bckup.p12', 'rb') as pkcs12_file:
# # 	pkcs12_data = pkcs12_file.read()

# p12 = crypto.load_pkcs12(open("C:\\Users\\bhans\\Downloads\\Fall 2019\\Crypto\\Project5\\Certificates\\cert_bckup.p12", 'rb').read(), b"CSE539_Rocks!")
# #pkcs12_password_bytes = "CSE539_Rocks!".encode('utf8')

# #pycaP12 = load_key_and_certificates(pkcs12_data, pkcs12_password_bytes, backend)

# # cert_bytes = pycaP12[1].signature
# # print("abc %s" %cert_bytes.hex())
# # pk_bytes = pycaP12[0].private_bytes(Encoding.PEM , PrivateFormat.PKCS8, NoEncryption())
# # print("def %s" %pk_bytes.hex())
# crypto.dump_certificate(type, cert)
# cert = x509.load_pem_x509_certificate(p12.get_certificate(), default_backend())
# print()


file_subject = open("C:\\Users\\bhans\\Downloads\\Fall 2019\\Crypto\\Project5\\Certificates\\subject.crt", 'rt')
cert_subject = crypto.load_certificate(crypto.FILETYPE_PEM,file_subject.read())
key_encoded = crypto.dump_certificate(crypto.FILETYPE_PEM,cert_subject)
print(key_encoded)
cert2 = x509.load_pem_x509_certificate(
    key_encoded,
    backend=default_backend())
print(cert2.signature.hex())
print(cert2.signature_hash_algorithm)