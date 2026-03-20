## 2026-01-29 - [AppNotificationBuilderUtility Optimization]
**Learning:** Returning small static containers (like std::unordered_map) by value can cause significant overhead in tight loops due to repeated copying. Additionally, performing string operations like `substr()` inside a loop for every character can be extremely expensive (~90% slower) compared to only performing them when a specific trigger character (e.g., '%') is encountered.
**Action:** Always return static containers by const reference. Use `reserve()` for string building when the size is known or can be estimated. Add early-exit checks in parsing loops to skip expensive substring/allocation operations.

## 2026-01-30 - [Optimizing small static lookups]
**Learning:** For very small sets of characters (e.g., 3-5), `std::unordered_map` lookups are significantly slower than a simple `switch` statement due to hashing overhead. Furthermore, direct character comparison at specific offsets is much faster than using `substr()` to create temporary strings for comparison.
**Action:** Replace map lookups with `switch` statements for small, fixed character sets. Avoid `substr()` in performance-sensitive loops.
