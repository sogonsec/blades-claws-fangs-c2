# Stuff C2 Commands Need To Do or Handle

The list below is a brainstorm of ideas and things that would be handy. All of these commands are secret and C2 operational stuff is hidden/clandestine from normal activity (although transferring a ton of data or using services, and agents, in an non-sneaky way could raise alarms if it is being monitored... like a ton of DNS requests at once that make no sense or appear odd).

I've never really used a C2 before, so this is mostly what I'd like to do if I had a compromised machine hooked up to my C2 server, that I could then make use of in a way that would be useful, especially if it would be a PITA to connect back to and do things (like say running a single command is multiple steps and having to parse through garbage). No idea now practical, but why not give it a shot. The bulk of the hard stuff will be on the agents.

Note: all network communications should be encrypted in transit tunnels and data, if possible, unless normal behavior sneakiness is the priority.

- authenticate and get a token (that allows a human/bot to do things with the server that is abnormal, otherwise it is simply a server running services that may or may not work well)
- report on services and status
- display authenticated history
- report on current agents/compromised machines (with an estimate of how reliable the agents/compromised machines are still owned and operational)
- run command on an agent
- read/write files via an agent
- privesc via agent
- persist via agent
- remove all trace from compromised machine via agent
- invalidate all tokens 
- kill all current client connections
- get an interactive shell via an agent (even if emulated)
- report on installed compromised system OS, patches, packages/apps install, users and groups, network info, uptime, system hardware stats (ram, cpu, disks, network cards, webcams, etc) via agent
- allow other users to the server to authenticate (key pair??)
- is the compromised machine on the Internet directly (via agent)
- compromised machine firewall rules (via agent)
- security protections enabled on compromised machine (via agent)
- winpeas/linpeas/linenum.sh output or compatible checks
- agent operational modes for detection (super sneaky or super loud/who cares, etc)
- shells (reverse and bound)
- agent check in with server every so often for commands to run (guess a queue will be required) or to let the server know they're still alive.
