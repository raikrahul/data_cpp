# Problem 27: Equal/Mismatch Derivation

01. Define Start Address v1: 0x1000.  + Code: // none
02. Define Start Address v2: 0x2000.  + Code: // none
03. Define Element Size: 4 bytes.     + Code: // none

04. Calculate v1[0] addr → 0x1000. Val = 1.
05. Calculate v2[0] addr → 0x2000. Val = 1.
06. Compare v1[0] == v2[0] → 1 == 1 → ✓ (True). Continue.

07. Calculate v1[1] addr → 0x1000 + 4 = 0x1004. Val = 2.
08. Calculate v2[1] addr → 0x2000 + 4 = 0x2004. Val = 2.
09. Compare v1[1] == v2[1] → 2 == 2 → ✓ (True). Continue.

10. Calculate v1[2] addr → 0x____ + _ = 0x____. Val = ____.
11. Calculate v2[2] addr → 0x____ + _ = 0x____. Val = ____.
12. Compare v1[2] == v2[2] → ____ == ____ → _ (True/False). Action: ____.

13. Calculate v1[3] addr → 0x____ + _ = 0x____. Val = ____.
14. Calculate v2[3] addr → 0x____ + _ = 0x____. Val = ____.
15. Compare v1[3] == v2[3] → ____ == ____ → _ (True/False). Action: ____.

16. SURPRISE: Mismatch detected at Index 3.
17. Stop iteration immediately? Yes/No: ____.
18. Return value of std::equal? True/False: ____.

19. Write std::equal syntax: std::equal(start1, end1, start2).
20. Arg 1: v1.begin() → Iterator to 0x1000.
21. Arg 2: v1.end()   → Iterator to 0x1000 + 5*4 = 0x1014 (Past-the-end).
22. Arg 3: v2.begin() → Iterator to 0x2000.

23. PREDICT FAILURE: v2 is shorter than v1?
24. Scenario: v1 size 5, v2 size 3.
25. Access v2[3] → 0x2000 + 12 = 0x200C.
26. If v2 ended at 0x200C, accessing it is Buffer Overflow ✗.
27. Does std::equal check v2 size? No. (Surprise!)
28. Conclusion: User MUST ensure v2 size >= v1 size.
