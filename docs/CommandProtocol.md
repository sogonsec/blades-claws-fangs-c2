# Stuff C2 Commands Need To Do or Handle

The list below is a brainstorm of ideas and things that would be handy. All of these commands are secret and C2 operational stuff is hidden/clandestine from normal activity (although transferring a ton of data or using services, and agents, in an non-sneaky way could raise alarms if it is being monitored... like a ton of DNS requests at once that make no sense or appear odd).

Note: all network communications should be encrypted in transit tunnels and data, if possible, unless normal behavior sneakiness is the priority.

- authenticate and get a token (that allows a human/bot to do things with the server that is abnormal, otherwise it is simply a server running services that may or may not work well)
- report on services and status
- display authenticated history
- report on current agents/compromised machines
- run command on an agent
- read/write files via an agent
- privesc via agent
- persist via agent
- remove all trace from compromised machine via agent
- invalidate all tokens 
- kill all current client connections
- get an interactive shell via an agent (even if emulated)
- report on installed compromised system OS, patches, packages/apps install, users and groups, network info, system stats (ram, cpu, disks, network cards, webcams, etc) via agent
- allow other users to the server to authenticate (key pair??)
- is the compromised machine on the Internet directly (via agent)
- compromised machine firewall rules (via agent)
- security protections enabled on compromised machine (via agent)
- winpeas/linpeas/linenum.sh output or compatible checks
- agent operational modes for detection (super sneaky or super loud/who cares, etc)
- shells (reverse and bound)