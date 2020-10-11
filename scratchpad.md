# Overall Design

Maybe not an MVP goal, but ideally everything should be modular and operate in a plugin sort-of-way. 

# Agents

Agents should not submit floods of requests as that would be abnormal activity, opting to space out requests. Avoiding detection is a top priority, at the expense of speed or even rich functionality (unless it is a hail mary all-in push)

# DNS communication module

Use DKIM strings for communication (and possibly other TXT messages that long strings?). A knock dns request option should exist to trigger the non-standard activity, that would default to being enabled (DNS should operate as a normal DNS server if not knocked).

https://tools.ietf.org/html/rfc1035 RFC for protocol spec.

- Perl https://metacpan.org/pod/Net::DNS::Nameserver#EXAMPLE if not wanting to code myself AND use perl
    - https://metacpan.org/pod/Moose revisit Moose if doing something of substance
        - Moose also allows ease in hooking into subroutines using method modifiers, possibly allowing plugin ability by default?? https://metacpan.org/pod/distribution/Moose/lib/Moose/Manual/Concepts.pod#Method-modifiers
- Python example/POC if coding myself, which should be somewhat portable to other languages https://www.youtube.com/watch?v=HdrPWGZ3NRo (9 video series) 

There's enough room in DKIM TXT for commands and output (mostly, need to explore compression and ascii encoding to fit in 512 byte - header]. Unsure how best to have agents know to query, other than regularly poll possible server communication mechanisms until something works. 

There's other DNS requests that are in the RFC that I haven't encoutered before, but could allow longer data payloads. It would be cool to hide data within the payload or something else that would be disregarded or ignored by the protocol itself but still not cause an error where it would only be found with reverse engineering the payload. Possibly going into the weeds there, but fun to think about. 

# Plugin Core

Figure out how best to handle having new connections or new data coming from a socket being a plugin event, or abandon the idea as something impractical. There needs to be a main loop, but perhaps protocol specific servers (DNS tcp/udp or HTTP/HTTPS) could be their own plugin themselves. It would be still be applicable for a main loop on raw sockets though (perhaps another plugin provided service itself?!).

Need to figure out how best to allow plugins to have all the relevant information they need to operate well. So, need to pass a copy of the configuration class/state, mechanism to allow data transfer over other existing sockets, or information relevant to what is being executed such as receiving a line from a socket and then passing that to the plugin registered function).

# Communication bus

Does there need to be a communication bus between all functionality, to allow for communication across different sockets such as receiving data from one socket/service and then writing data to another socket/service. 

# Logging 

There should be a logging mechanism that should work across all plugins and core functionality. 

# Threading

How best to have data shared across all threads and is it even needed? When should threading be used (new services? logging? something not obvious yet)

# Event bus

Is there an already developed solution for event callback stuff? think signal/slots in Qt and other callback/signal/event mechanisms. 

# Coding steps

1. Write a configuration class to consume command line arguments and configuration files (ini?), to be available across every plugin and core.
2. Write a logging class to allow writing log messages by some mechanism (configurable) and may need to be threadsafe, to be available across every plugin and core
2. Write a plugin controller class, that allows functions to "register" to execute on plugin events. something like register_plugin('configuration_post_load', 'my_plugin_function'), and when the configuration is loaded normally, the plugin machinery would execute all functions at that time.
3. Write main function that executes the configuration class
4. Create plugin events for every function, at a minimum at the start and end of the function.
5. Stub out a DNS plugin and configuration 
