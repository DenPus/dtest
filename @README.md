@name v@version
====================================
@description

# Features

* no dependencies (only libc!)
* extremely small code footprint
* no dynamic memory allocation
* used C11 standard
* "asserts" support time differential
* used _Generic

# Usage

Download `@name\.h`, include it, done.

```
#include "@name\.h"

CASE(name) {
    assert_eq(5);
    assert_eq(5.0f, 5.0f);
    assert_eq(5.0l, 5.0l);
}

CASE(two) {
    assert_gt(5, 4);
    assert_gt(5.0f, 4.0f);
    assert_gt(5.0l, 4.0l);
}

SUITE(name, two);
```

# Info

* Language code: @language
* Author: Denpus
* License: @license
