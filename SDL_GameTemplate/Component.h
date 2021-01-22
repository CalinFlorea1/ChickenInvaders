#pragma once

class Component
{
public:
   virtual ~Component() = default;
   virtual void init(int inaltime = 850, int lungime = 900, int marime  = 150) = 0;
   virtual void update(int direction = 0) = 0;
   virtual void draw() = 0;
};