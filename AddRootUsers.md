#ifndef.io - ec2user

sudo adduser username

sudo passwd username

#Add user to sudoers file through visudo and add username ALL=(ALL:ALL) NOPASSWD:ALL

sudo visudo

#Change PassWordAuthentication no -> yes in /etc/ssh/sshd_config

sudo vim /etc/ssh/sshd_config

#Restart sshd for changes to take effect

sudo service sshd restart

#Test login and sudo su for root

ssh username@address

sudo su
