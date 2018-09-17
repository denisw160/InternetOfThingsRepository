// INPUT 0 true DemoUser
// buffer contains complete input telegram from target

buffer.position(8); // jump to payload index

var allocated = buffer.get(); // extract byte 1
self.log("allocation from target = " + allocated);
