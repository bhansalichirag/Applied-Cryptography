from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import padding
import sys
from OpenSSL import crypto
from cryptography import x509
from cryptography.hazmat.backends import default_backend

arguments = len(sys.argv) - 1   

def part6():
    print("6th part:")
    file_subject = open(sys.argv[3], 'rt')
    cert_subject = crypto.load_certificate(crypto.FILETYPE_PEM,file_subject.read())
    key_encoded = crypto.dump_publickey(crypto.FILETYPE_PEM,cert_subject.get_pubkey())
    pubkey2 = serialization.load_pem_public_key(
        key_encoded,
        backend=default_backend())
    message = b"Hello world"
    ciphertext = pubkey2.encrypt(
        message,
        padding.OAEP(
            mgf=padding.MGF1(algorithm=hashes.SHA256()),
            algorithm=hashes.SHA256(),
            label=None
        )
    )
    p12 = crypto.load_pkcs12(open(sys.argv[1], 'rb').read(), sys.argv[4].encode())

    key_encoded = crypto.dump_privatekey(crypto.FILETYPE_PEM,p12.get_privatekey(),None,sys.argv[4].encode())
    prikey2 = serialization.load_pem_private_key(
    key_encoded,password=None,
    backend=default_backend())
    plaintext = prikey2.decrypt(
        ciphertext,
        padding.OAEP(
            mgf=padding.MGF1(algorithm=hashes.SHA256()),
            algorithm=hashes.SHA256(),
            label=None
        )
    )
    print("Ciphertext: %s" %ciphertext.hex())
    print("Plaintext: %s" %plaintext)
    print("\n\n")

def part5():
    print("5th part:")
    file_subject = open(sys.argv[3], 'rt')
    cert_subject = crypto.load_certificate(crypto.FILETYPE_PEM,file_subject.read())
    key_encoded = crypto.dump_certificate(crypto.FILETYPE_PEM,cert_subject)
    #print(key_encoded) #check the value
    cert2 = x509.load_pem_x509_certificate(
        key_encoded,
        backend=default_backend())
    print("Hex signature : %s" %cert2.signature.hex())
    print("\n\n")

def part4():
    print("4th part:")
    file_root = open(sys.argv[2], 'rt')
    cert_root = crypto.load_certificate(crypto.FILETYPE_PEM,file_root.read())
    key_encoded = crypto.dump_publickey(crypto.FILETYPE_PEM,cert_root.get_pubkey())
    pubkey2 = serialization.load_pem_public_key(
    key_encoded,
    backend=default_backend())

    print("Root Public Key Modulus = %s" %pubkey2.public_numbers().n)
    print("Root Public Key Exponent = %s" %pubkey2.public_numbers().e)
    print("\n\n")
    

def part3():
    print("3rd part:")
    file_subject = open(sys.argv[3], 'rt')
    cert_subject = crypto.load_certificate(crypto.FILETYPE_PEM,file_subject.read())
    key_encoded = crypto.dump_publickey(crypto.FILETYPE_PEM,cert_subject.get_pubkey())
    pubkey2 = serialization.load_pem_public_key(
    key_encoded,
    backend=default_backend())

    print("Public Key Modulus = %s" %pubkey2.public_numbers().n)
    print("Public Key Exponent = %s" %pubkey2.public_numbers().e)
    
    p12 = crypto.load_pkcs12(open(sys.argv[1], 'rb').read(), sys.argv[4].encode())

    key_encoded = crypto.dump_privatekey(crypto.FILETYPE_PEM,p12.get_privatekey(),None,sys.argv[4].encode())
    prikey2 = serialization.load_pem_private_key(
    key_encoded,password=None,
    backend=default_backend())

    #print("Public Key Modulus = %s" %prikey2.)
    print("Private Key Exponent = %s" %prikey2.private_numbers().d)
    print("\n\n")

def part2():
    print("2nd part:")
    file_subject = open(sys.argv[3], 'rt')
    cert_subject = crypto.load_certificate(crypto.FILETYPE_PEM,file_subject.read())
    key_encoded = crypto.dump_certificate(crypto.FILETYPE_PEM,cert_subject)
    cert2 = x509.load_pem_x509_certificate(
        key_encoded,
        backend=default_backend())
    subject = cert_subject.get_subject()
    print("Subject name = %s" %subject.CN)    # the Common Name field
    Issuer = cert_subject.get_issuer()
    print("Issuer = %s" %Issuer.CN)
    print("Serial number = %d" %cert_subject.get_serial_number())
    # print("Encryption Algo = %s" %cert_subject.get_signature_algorithm()) #sign algo
    print("Encryption Algo = %s" %cert2.signature_hash_algorithm.name)#sign hash algo
    print("Not Valid Before = %s" %cert_subject.get_notBefore())
    print("Not Valid After = %s" %cert_subject.get_notAfter())
    print("\n\n")

def part1():
    
    file_root = open(sys.argv[2], 'rt')
    cert_root = crypto.load_certificate(crypto.FILETYPE_PEM,file_root.read())
    store = crypto.X509Store()
    store.add_cert(cert_root)
    file_subject = open(sys.argv[3], 'rt')
    cert_subject = crypto.load_certificate(crypto.FILETYPE_PEM,file_subject.read())
    ctx = crypto.X509StoreContext(store, cert_subject)
        # Start validation
    print("1st part:")
    try:
        ctx.verify_certificate()
        print("True")
    except crypto.X509StoreContextError as e:
        # print("False %s" % e)
        print("False")
    print("\n\n")


if arguments < 4 :  #check the number of arguments    #uncomment later in the program
        print("Number of arguments are less")
        exit(0)
part1()
part2()
part3()
part4()
part5()
part6()
#print("Done")
