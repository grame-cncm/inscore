//-----------------------------------------------
// An INScore plugin that makes the sum of the
// signals as follows:
//   out0 = in0
//   out1 = in0 + in1
//   out2 = in0 + in1 + in2
// see stack.svg for the block diagram
//-----------------------------------------------

stack(1) = _;
stack(2) = split , _ : _,+;
stack(n) = ( stack(n-1) : bus(n-2),split ), _: bus(n-1),+;

split= _ <: _,_;
bus(n) = par(i,n,_);
vol(n) = par(i,n, *(vslider("volume", 1, 0, 1, 0.01)));

process = stack(3) : vol(3);
