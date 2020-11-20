in0 :: FromDPDKDevice(0);
out0 :: ToDPDKDevice(0);
in1 :: FromDPDKDevice(1);
out1 ::ToDPDKDevice(1);

class_left :: Classifier(12/0806 20/0001,  //ARP query
                         12/0806 20/0002,  // ARP response
                         12/0800); //IP

class_right :: Classifier(12/0806 20/0001,  //ARP query
                         12/0806 20/0002,  // ARP response
                         12/0800); //IP

in0 -> class_left;
in1 -> class_right;

class_left[0] -> out1;
class_left[1] -> out1;
class_right[0] -> out0;
class_right[1] -> out0;

fw :: IPFilter();

class_left[2] -> 