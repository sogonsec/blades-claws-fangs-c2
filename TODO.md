Never built one of these but I can figure it out. This TODO may seem silly at first, because I've never done it and just trying to get what I think I need to do planned out. 

Reference https://attack.mitre.org/tactics/TA0011/ to try to be "compliant" to or use as a spec.

# Server / Generic

* Create command protocol, a common way of signaling to do things using Stargate references
* Create a generic library to handle command protocol independent of the service/agent 
* Create application protocol service mechanisms (the idea is to hide from casual onlookers and try to not seem out of the ordinary, but obviously not entirely hidden)
    * Create HTTP service, perhaps encode the payload in a header 
    * Create DNS service, perhaps using common TXT keys or DKIM? 
    * Create ICMP service, spaced out icmp payload transfer... at something like 56 bytes at a time? 
    * Create FTP service, perhaps leveraging password and response (need to look at the command protocol)
    * Create SMTP service, perhaps hiding within a server response where a message ID or similiar would be shown
* Figure out how to handle encryption of payloads (perhaps different for each service, unique key pair per agent? no idea)
* Figure out how to use data obfuscation of payloads

# Agent - Windows

* Create windows service agent in C
* Create powershell agent
* Create ASPX agent

# Agent - Linux

* Create systemd service agent
* Create kernel module agent
* Create docker service agent
* Create PHP agent

# Agent - FreeBSD

* Create kernel module agent

