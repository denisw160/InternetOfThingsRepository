// OUTPUT 0 true DemoUser
// buffer contains complete output telegram from server

buffer.position(8); // jump to playoad index

// define byte array for payload
var payload = Java.to([0], "byte[]");

// Allocation state
var allocated = t.getStatus("allocated");
self.log("allocation state = " + allocated);

h.setBit(payload, 0, allocated == true);

// put payload into buffer
buffer.put(payload);

// checksum will be automatically added by system
