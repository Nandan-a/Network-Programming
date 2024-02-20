import paramiko 
import getpass
import time

ip_add=input("please enter th ip address of the device:")
usr_name=input("Enter device ")
password=getpass.getpass()
loopback=input("Plese enter loopback number")

ssh_client=paramiko.SSHClient()
ssh_client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
ssh_client.connect(hostname=ip_add,username=usr_name,password=password)

print("Successfull connection")
#rc=Remote_connection

rc=ssh_client.invoke_shell()