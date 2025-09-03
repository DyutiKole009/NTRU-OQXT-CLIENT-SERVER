# NTRU-OQXT-CLIENT-SERVER

The primary objective of this project is to separate the server and client implementations with secure socket connections, enabling post-quantum setup and search in [NTRU-OQXT](https://github.com/debadrita05/NTRU-OQXT.git) - a prototype implementation of the highly efficient post-quantum secure conjunctive SSE scheme from the paper *Highly Scalable Searchable Symmetric Encryption for Boolean Queries from NTRU Lattice Trapdoors*, *Debadrita Talapatra, Indian Institute of Technology Kharagpur, Sikhar Patranabis, IBM Research India, and Debdeep Mukhopadhyay, Indian Institute of Technology Kharagpur* published by the International Association for Cryptologic Research in *IACR Communications in Cryptology (CIC)*, Volume 2, Number 2, 2025. 
DOI: [10.62056/ae89n59p1](https://doi.org/10.62056/ae89n59p1). 

The server code shall run inside a CentOS virtual machine hosted via QEMU, while the client code will run on the local machine. A secure communication channel is established between the client and server using TCP socket connections. The codebase is implemented in C/C++.

## System Requirements

For system requirements and dependencies, follow [TWINSSE](https://github.com/SEAL-IIT-KGP/TWINSSE/tree/main?tab=readme-ov-file) github repo. 

## Dependencies

The following packages (development versions) must be installed with global linkage.

  [Redis] redis v5:4.0.9, redis-server v5:4.0.9, redis-tools v5:4.0.9, libhiredis-dev v0.13.3-2.2

  [redis++] Install from https://github.com/sewenew/redis-plus-plus

  [Blake3] Install Blake3 package from https://github.com/BLAKE3-team/BLAKE3

  [CryptoPP] libcrypto++-dev v5.6.4, libcrypto++-utils v5.6.4, libcrypto++6 v5.6.4

  [Falcon] To leverage efficient implemntations of lattice-based tradoors from Falcon, the Falcon reference implementation must be installed from https://falcon-sign.info/

## Running the experiments

`server` is the server side code and should be placed in the virtual machine while `client` is the client side code and should be placed in local machine.

### Launching qemu

Since the server code binds to port 8080 inside the CentOS virtual machine, QEMU is launched with port forwarding enabled, mapping a port on the host to port 8080 in the guest, to allow the client running locally to communicate with the server.

```
qemu-system-x86_64 \
  ... \
  -net nic \
  -net user,hostfwd=tcp::8080-:8080 \
  ...
```

In case of connection issues, disabling the firewall on CentOS may be necessary.

```
sudo systemctl stop firewalld
```

Navigate to `OXT_CONJ_CLIENT/client` in client(local machine) and to `OXT_CONJ_SERVER/server` in server(virtual machine).

### NTRU-OQXT Setup

Follow the makefiles to build the targets `oqxt_falcon_setup_client` and `oqxt_falcon_setup_server` in the client and server respectively.

Run in server,

```
./oqxt-falcon_setup_server
```
and then in client,
```
./oqxt-falcon_setup_client
```

Client will read the database and send the server: 
* TSet entries (which are written to the redis database in the server)
* XSet bloomfilter (written to the disk as `bloomfilter.dat`)

### NTRU-OQXT Search

Follow the makefiles to build the targets `oqxt-falcon_setup_client` and `oqxt-falcon_setup_server` in the client and server respectively.

Run in server,

```
make oqxt-falcon_setup_server
```
and then in client,

```
make oqxt-falcon_setup_client
```

Run in server,

```
make oqxt-falcon_search_server
```
and then in client,

```
make oqxt-falcon_search_client
```

Note that `client/results` currently has `input.txt` and `exp_output.txt` with 4 conjunctive queries.

Also note that the variable `n_iterations` in `client/oqxt-falcon_search_client.cpp` should be initialized with a value greater than the number of lines in `input.txt`.

Finally, 
Run in server,

```
./oqxt-falcon_search_server
```
and then in client,

```
./oqxt-falcon_search_client
```

## Visualization of the Work

### Client Side View after Setup Phase
<img src="https://drive.google.com/uc?export=view&id=1SGU9ra1NIC4Sh2thIrnBuSS6jVSCgYF5" width="400">

### Server Side View after Setup Phase
<img src="https://drive.google.com/uc?export=view&id=1rZiI5vO1qW2IgCprh470YvtAe_9fRAXw" width="400">

### Client Side View after Search Phase
<img src="https://drive.google.com/uc?export=view&id=1aBum3nL4xkGFa9fs2OsZJ_U2SJ62cyrX" width="400">

### Server Side View after Search Phase
<img src="https://drive.google.com/uc?export=view&id=1h75DA95xesIhIa9mqEV6uWeKzU4fNIDu" width="400">
<img src="https://drive.google.com/uc?export=view&id=1Uog4KgdiL7wTVP4yBMymm4ZUtiLCvhQy" width="400">
