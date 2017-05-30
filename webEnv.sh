#!/bin/bash

echo "-->Updating Amazon Linux"
sudo yum -y update

echo "-->Installing required packages"
sudo yum install -y httpd24 php70 mysql56-server php70-mysqlnd mod24_ssl

echo "-->Starting apache and configuring auto-start"
sudo service httpd start
sudo chkconfig httpd on

echo "-->Configuring permissions for www group"
sudo groupadd www
sudo usermod -a -G www ec2-user
sudo chown -R ec2-user:www /var/www
sudo chmod 2775 /var/www
find /var/www -type d -exec sudo chmod 2775 {} \;
find /var/www -type f -exec sudo chmod 0664 {} \;

echo "-->Starting mysql and configuring auto-start"
sudo service mysqld start
sudo chkconfig mysqld on

echo "-->Configuring permissions for apache"
sudo usermod -a -G www apache
sudo chown -R apache /var/www
sudo chgrp -R www /var/www
sudo chmod 2775 /var/www
find /var/www -type d -exec sudo chmod 2775 {} \;
find /var/www -type f -exec sudo chmod 0664 {} \;
sudo service httpd restart

echo "-->Downloading certbot for LetsEncrypt and configuring permissions"
wget https://dl.eff.org/certbot-auto
chmod a+x certbot-auto

echo "******************************************"
echo "Configure mysql with the following command"
echo "sudo mysql_secure installation"
echo "******************************************"
echo "Configure certbot-auto with the following"
echo "sudo ./certbot-auto --debug -v --server https://acme-v01.api.letsencrypt.org/directory certonly -d example.com"
echo "******************************************"
echo "Paths for SSl CertificateFile / CertificateKeyFile / CertificateChainFile"
echo "/etc/letsencrypt/live/example.com/cert.pem"
echo "/etc/letsencrypt/live/example.com/privkey.pem"
echo "/etc/letsencrypt/live/example.com/fullchain.pem"
echo "******************************************"



