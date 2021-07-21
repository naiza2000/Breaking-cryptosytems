#!/usr/bin/expect 
set timeout -1
log_file ssh_outputs.log
spawn  ssh -t  student@65.0.124.36
 
expect "id_rsa':"