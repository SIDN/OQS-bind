# OQS-bind

SIDN Labs' OQS-bind is a fork of deSEC's and Jason Goertzen's OQS-bind, which is a fork of ISC's BIND9.
This fork take advantage of [Open Quantum Safe](https://github.com/open-quantum-safe)'s
[liboqs](https://github.com/open-quantum-safe/liboqs) and [oqs-provider](https://github.com/open-quantum-safe/oqs-provider).
**NOTE:** OpenSSL 3.2 is **REQUIRED** to build and use OQS-Bind.

This project is not officially affiliated with Open Quantum Safe.

## Algorithms primarily supported by our fork
|            Algorithm         | DNSSEC Algorithm ID |
| ---------------------------- | ------------------- |
|           MAYO-2             |         249         |
|           Falcon-512         |         251         |

## Building

In order to build OQS-bind, some version of OpenSSL 3.2+ must be installed.
We build OQS-bind [as shown here](https://github.com/SIDN/OQS-bind-container/blob/main/Dockerfile).

