#ifndef FILTERS_H
#define FILTERS_H

// Simple first-order difference eqn filter to LP the signal
class LowPass{
    float alpha;
    float old;
    public:
    LowPass(float a, float initial=0){
      alpha = a;
      old = initial;
    }
    float step(float input){
      old = alpha*old + (1-alpha)*input;
      return old;
    }
    void set(float value){
      old = value;
    } 
};

#endif
