# Overall Design

Maybe not an MVP goal, but ideally everything should be modular and operate in a plugin sort-of-way. 

# Agents

Agents should not submit floods of requests as that would be abnormal activity, opting to space out requests. Avoiding detection is a top priority, at the expense of speed or even rich functionality (unless it is a hail mary all-in push)

# DNS communication module

Use DKIM strings for communication (and possibly other TXT messages that long strings?). A knock dns request option should exist to trigger the non-standard activity, that would default to being enabled (DNS should operate as a normal DNS server if not knocked).

https://tools.ietf.org/html/rfc1035 RFC for protocol spec.

There's enough room in DKIM TXT for commands and output (mostly, need to explore compression and ascii encoding to fit in 512 byte - header]. Unsure how best to have agents know to query, other than regularly poll possible server communication mechanisms until something works. 

