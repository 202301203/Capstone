Capstone Project P9 Section B
TeamId : DSA

Group Members : 
Tandel Dhruvinee Dineshkumar     (ID : 202301203)
Jogadiya Dhara R.                (ID : 202301195)
Jobanputra Dhruvi Himanshu       (ID : 202301401)
Rutu chaudhari                   (ID : 202301235)

P9. TV Channel Scheduler:
You are to build a TV Channel Scheduler. The Scheduler works for family
members who want to record their favorite TV series so that they can watch
them later and get notified by the Scheduler when they have time (it knows their
availability slots - randomly initialized). There are N members in a family, each
having their favorite series out of a total of M. Multiple members may love the
same series. However, the Scheduler cannot schedule a series if there is a
conflict of interest. Also, members want to get on time for p slots. The Scheduler
needs to minimize total episode misses.

Data Structure that is used : 
Vectors: Vectors are widely used to store dynamic arrays of objects. 
        They are used for storing various elements such as series, members, TV shows, slots, etc. 
        Vectors are used in place of arrays. Because they provide dynamic resizing, efficient element access, and ease of use.

Unordered_map: Unordered_map is used for implementing hash tables. 
                It is used in the HashTable class to map keys to values. 
                Unordered maps provide constant-time average complexity and are suitable for implementing associative arrays where the order of elements is not important.
                We have 2 Unordedred_map, in first we map slot ID  to series that air at that particular slot. 
                And in other we have mapped seriesid to member that like that series. 
                So we can grab easy access over series time and associated member with that series airing on slot.  

Priority Queue: Priority queue is used to prioritize slots based on certain criteria. 
                It is used in the TVScheduleFunction to prioritize slots for scheduling TV shows.
                Priority queues are chosen because they automatically sort elements based on predefined comparison criteria, ensuring efficient retrieval of the highest priority element.
                Here we have given a constraint where each member should at least get p slots. So by using priority_queue we prioritize  that member who got lesser slots in comparison to others. 

Overall, these data structures are chosen based on their suitability for specific tasks within the program.
such as efficient storage, retrieval, prioritization, and organization of data.

What Do we Understand By this Problem? :


