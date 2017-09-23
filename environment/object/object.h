// Four properties that contain the whole object in the coordinate system
// double x
// double y
// width
// height

// provide virtual method for collision detection. Two objects
// should polymorhically compare if they collide with each other
// based on their coordinate and their internal structure.
// base class implementation will test collision based on rectangle
// information. For precision the polymorphic implementation can
// be used (important for complex objects when another object is close
// to rectangle)
