
# Capstone Project P9 Section B
# P9. TV Channel Scheduler

You are to build a TV Channel Scheduler. The Scheduler works for family
members who want to record their favorite TV series so that they can watch
them later and get notified by the Scheduler when they have time (it knows their
availability slots - randomly initialized). There are N members in a family, each
having their favorite series out of a total of M. Multiple members may love the
same series. However, the Scheduler cannot schedule a series if there is a
conflict of interest. Also, members want to get on time for p slots. The Scheduler
needs to minimize total episode misses.


## TeamId : DSA

- Tandel Dhruvinee Dineshkumar[-202301203](https://www.github.com/202301203)
- Jogadiya Dhara R. [-202301195](https://www.github.com/202301195)
- Jobanputra Dhruvi Himanshu [-202301401](https://www.github.com/202301401)
- Rutu chaudhari [-202301235](https://www.github.com/202301235)

## Data Structure that is used : 
- Vectors: Vectors are widely used to store dynamic arrays of objects. 
        They are used for storing various elements such as series, members, TV shows, slots, etc. 
        Vectors are used in place of arrays. Because they provide dynamic resizing, efficient element access, and ease of use.

- Unordered_map: Unordered_map is used for implementing hash tables. 
                It is used in the HashTable class to map keys to values. 
                Unordered maps provide constant-time average complexity and are suitable for implementing associative arrays where the order of elements is not important.
                We have 2 Unordedred_map, in first we map slot ID  to series that air at that particular slot. 
                And in other we have mapped seriesid to member that like that series. 
                So we can grab easy access over series time and associated member with that series airing on slot.  

- Priority Queue: Priority queue is used to prioritize slots based on certain criteria. 
                It is used in the TVScheduleFunction to prioritize slots for scheduling TV shows.
                Priority queues are chosen because they automatically sort elements based on predefined comparison criteria, ensuring efficient retrieval of the highest priority element.
                Here we have given a constraint where each member should at least get p slots. So by using priority_queue we prioritize  that member who got lesser slots in comparison to others. 

Overall, these data structures are chosen based on their suitability for specific tasks within the program.
such as efficient storage, retrieval, prioritization, and organization of data.
## What was our approach for this Problem? 
-  We have given information of members of a family along with their favorite series,and availability slots. We have created a TVChanel Scheduler that assigns member to a particular slot, if the show is on air and member is free. furthemore we have checked if there is a conflict between members, that is 2 or more members having same time slots but different favourite series that are on air. If we cannot schedule a series than scheduler will make data of series to be recorded based on priority given to member having watched less series. In additional we have also scheduled the recorded series randomly, that can help family members to minimize total number of misses. We have created a Notification Function. This function gives a pop-up notification and an hour before the member has assigned to a slot.
## Contribution:
- All the members have equally contributed in the understanding of the question and generating algorithm of the code.
- Here are some special parts that each member have handled individually.
1. Dhruvinee(202301203) - Writing TVChenal Scheduler Function,handling conflict function and some miscellaneous class.(35%)

2. Dhara(202301195) - Writing Notification function.(25%)

3. Dhruvi(202301401) - Writing function that schedule recorded series.(20%)

4. Rutu(202301235) - Writing function to sort vector and printing it.(20%)
