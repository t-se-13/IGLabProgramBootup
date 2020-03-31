#pragma once
#include "COMMON/OglForCLI.h"

#pragma unmanaged 


#define FLOOR_WIDTH  0.8f
#define FLOOR_LENGTH 1.45f
#define WALL_HEIGHT  0.1f

class SolidBall
{
private:
  float m_radius;
  float m_mass  ;
  
  EVec3f m_position;
  EVec3f m_velocity;

  EVec3f m_angle    ;
  EVec3f m_anglevel;

  //simulation 1stepにおいて付加された力とトルク
  EVec3f m_force_onestep;
  EVec3f m_torque_onestep;

public: 
  SolidBall(EVec3f pos, EVec3f vel, EVec3f angle, EVec3f anglevel);
  ~SolidBall();
  SolidBall( const SolidBall &src) { Copy(src); }
  SolidBall &operator=(const SolidBall &src){ Copy(src); return *this;}
  
  void Copy(const SolidBall &src) 
  {
    this->m_radius    = src.m_radius;
    this->m_mass      = src.m_mass;
    this->m_position  = src.m_position;
    this->m_velocity  = src.m_velocity;
    this->m_angle     = src.m_angle;
    this->m_anglevel = src.m_anglevel; 
    this->m_force_onestep = src.m_force_onestep;
    this->m_torque_onestep = src.m_torque_onestep;
  }

  void Draw();
  void Step( float h );
  EVec3f GetPos(){ return m_position; }
  EVec3f GetVel() { return m_velocity; }
  EVec3f GetAngle() { return m_angle; }
  EVec3f GetAngleVel() { return m_anglevel; }
  EVec3f GetForce() { return m_force_onestep; }
  EVec3f GetTorque() { return m_torque_onestep; }
  float GetRadius() { return m_radius; }
  float GetMass() { return m_mass; }
  void SetPos(const EVec3f& pos) { m_position = pos; }
  void SetVel(const EVec3f& vel){ m_velocity = vel; }
  void SetAngle(const EVec3f& angle) { m_angle = angle; }
  void SetAngleVel(const EVec3f& anglevel) { m_anglevel = anglevel; }
  void SetForce(const EVec3f& force) { m_force_onestep = force; }
  void SetTorque(const EVec3f& torque) { m_torque_onestep = torque; }
  bool isGrasped(const EVec3f& cursorPos, const EVec3f& cursorDir);
  bool isCollisionTable();
  bool isCollisionBall(SolidBall& ball);
};


class EventManager
{
private:
  EventManager();

  bool m_btn_right, m_btn_left, m_btn_middle;
  int m_GraspedBall;
  EVec3f m_shotF;
  std::vector<SolidBall> m_balls;
public: 
  static EventManager* GetInst(){
    static EventManager p;
    return &p;
  }

  void BtnDownLeft  (int x, int y, OglForCLI *ogl);
  void BtnDownMiddle(int x, int y, OglForCLI *ogl);
  void BtnDownRight (int x, int y, OglForCLI *ogl);
  void BtnUpLeft    (int x, int y, OglForCLI *ogl);
  void BtnUpMiddle  (int x, int y, OglForCLI *ogl);
  void BtnUpRight   (int x, int y, OglForCLI *ogl);
  void MouseMove    (int x, int y, OglForCLI *ogl);
  void Button_1     ();
  void Button_2     ();

  void DrawBilliardTable();
  void DrawScene();

  void Step();

  void CollideTable(SolidBall& ball);
  void CollideBall(SolidBall& ball1, SolidBall& ball2);
};



#pragma managed

