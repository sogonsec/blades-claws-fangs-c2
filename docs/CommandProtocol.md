# Stuff C2 Commands Need To Do or Handle

The list below is a brainstorm of ideas and things that would be handy. All of these commands are secret and C2 operational stuff is hidden/clandestine from normal activity (although transferring a ton of data or using services, and agents, in an non-sneaky way could raise alarms if it is being monitored... like a ton of DNS requests at once that make no sense or appear odd).

I've never really used a C2 before, so this is mostly what I'd like to do if I had a compromised machine hooked up to my C2 server, that I could then make use of in a way that would be useful, especially if it would be a PITA to connect back to and do things (like say running a single command is multiple steps and having to parse through garbage). No idea now practical, but why not give it a shot. The bulk of the hard stuff will be on the agents.

Note: all network communications should be encrypted in transit tunnels and data, if possible, unless normal behavior sneakiness is the priority.

I may want to consider making the protocol binary instead of ascii. It would use less bytes and have less strings in the binaries and streams. As long as the protocol is easy for humans to figure out when coding (documentation) then it shouldn't be that big a deal. I'm writing it so I get the luxury of doing what I want :) Probably want a decoder/encoder from ascii to binary anyways for the compression/encryption/obfuscation stuff anyways, so bake it in... probably a few pages of defines or an array of bytes with the ascii in comments for humans... should be able to fit a command in a byte or three, and then payload (where applicable after). 

- playbook for doing actions from the agent to the server (such as "normal" email sending: resolve domain, check spf, check DKIM, check MX, send SMTP email) to appear clandestine and not ring any blue team bells (casually... of course good blue teams will know which DNS and SMTP servers you're supposed to use in corp networks, but got to at least try)
    - words: playbook get set neveruse ignore execute
- domain names for server
    - words: domain get set update change rotate random order swiss
- authenticate and get a token (that allows a human/bot to do things with the server that is abnormal, otherwise it is simply a server running services that may or may not work well)
    - words: auth authenticate token session
- report on services and status
    - words: report service services stat status
- display authenticated history
    - words: display auth authenticated hist history
- report on current agents/compromised machines (with an estimate of how reliable the agents/compromised machines are still owned and operational)
    - words: report agents machines operational owned alive current
- run command on an agent
    - words: command cmd run
- read/write files via an agent
    - words: files file read write in out save download upload
- privesc via agent
    - words: privup privesc get system admin root sudo super su
- persist via agent 
    - words: persist infest persistence burrow
- remove all trace from compromised machine via agent
    - words: wipe cleanup remove trace sanitize
- invalidate all tokens 
    - words: invalidate all token tokens sessions session
- kill all current client connections
    - words: disconnect kill all client net network stop dark
- get an interactive shell via an agent (even if emulated)
    - words: get shell terminal interactive repl
- report on installed compromised system OS, patches, packages/apps install, users and groups, network info, uptime, system hardware stats (ram, cpu, disks, network cards, webcams, etc) via agent
    - words: report system info all os patches apps users groups network uptime hardware
- allow other users to the server to authenticate (key pair??)
    - words: grant add permit admin access user key
- is the compromised machine on the Internet directly (via agent)
    - words: internet ip bound
- compromised machine firewall rules (via agent)
    - words: firewall fw rules 
- security protections enabled on compromised machine (via agent)
    - words: security sec prot protections enabled en
- winpeas/linpeas/linenum.sh output or compatible checks
    - words: enum enumerate local locally 
- agent operational modes for detection (super sneaky or super loud/who cares, etc)
    - words: oper operate operational mode 
- shells (reverse and bound)
    - words: shell sh reverse bind bound rev
- agent check in with server every so often for commands to run (guess a queue will be required). This is mainly for compromised hosts that may not be directly routable or addressable, like if it is behind a NAT or FW blocks inbound but not outbound, etc. Probably need more thought into a queue because a single queue item could take multiple protocol requests to get the entire thing (like say if you were depositing a binary file)
    - words: queue check get next id 
- agent heartbeat to let the server know the agent is still operational (configurable if enabled and needs to have non-static timing/behavior)
    - words: phonehome heartbeat checkin ping newphone whodis

