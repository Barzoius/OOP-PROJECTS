public class SpaceShip {

    private String m_Name;

    private double m_Speed;

    private double m_dirAngle; //in radians

    private Coordinates m_Coords;

    SpaceShip(String name, double speed, double dirAngle)
    {
        this.m_Name = name;
        this.m_Speed = speed;
        this.m_dirAngle = dirAngle;
    }


    public String getName(){
        return m_Name;
    }
    public void setName(String name){
        this.m_Name = name;
    }

    public double getSpeed(){
        return m_Speed;
    }
    public void setSpeed(double speed){
        this.m_Speed = speed;
    }

    public double getDirectionAngle() {
        return m_dirAngle;
    }

    public void setDirectionAngle(double dirAngle) {
        this.m_dirAngle = dirAngle;
    }

    public Coordinates getCoordinates() {
        return m_Coords;
    }
    public void setCoordinates(Coordinates coords) {
        this.m_Coords = coords;
    }
}
