# Core - Server
- Handle creation of sockets for services and tie into libevent
- Support plugins, even if simply using glib for it now via gmodule
- Create a generic command protocol and library, that other services and agents conform to (data transfer, commands, info, etc)
- Support the SMTP service
- Support the DNS service
- Support the HTTP service
- Support the ICMP service
- Add data encryption, compression, and obfuscation support
- Add multi-user authentication and tokens support (even if there's only one user)

# Extra - Server
- Add Python plugin support
- Add Lua plugin support
- Add IRC bot
- Add Slack bot
- Add Discord bot
