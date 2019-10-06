# UnixDataProcessor

A simple yet elegant unix data processor using C system calls for pipelines, forks and execute statements to create a audio 
frequency parser. Mutiple biquad instances are created by cascading the processes in pipes using fork statements such that
STD_OUT of each biquad gets sent to STD_IN of following biquad filters. 

Disclaimer: Project was a part of University of Toronto Systems Programming Course and was worked on from June 2019- July 2019.
