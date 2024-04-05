import java.time.Duration;
import java.time.Instant;

public class SpaceShip {

    private String m_Name;

    private double m_speed;

    private double m_dirAngle; //in radians

    private Coordinates m_Coords;

    private Instant m_lastAccessTime;

    private Coordinates m_destinationCoords;

    private double m_distance;

    SpaceShip(String name, double speed, double dirAngle)
    {
        this.m_Name = name;
        this.m_speed = speed;
        this.m_dirAngle = dirAngle;
        this.m_distance = 0;

        this.m_Coords = new Coordinates(0.0, 0.0, 0.0);

        this.m_lastAccessTime = Instant.now();
    }


    public String getName(){
        updateTime();
        return m_Name;
    }

    public void setName(String name){
        updateTime();
        this.m_Name = name;
    }

    public double getSpeed(){
        return m_speed;
    }
    public void setSpeed(double speed){
        updateTime();
        this.m_speed = speed;
    }

    public double getDirectionAngle() {
        updateTime();
        return m_dirAngle;
    }

    public void setDirectionAngle(double dirAngle) {
        updateTime();
        this.m_dirAngle = dirAngle;
    }

    public Coordinates getCoordinates() {
        updateTime();
        return m_Coords;
    }
    public void setCoordinates(Coordinates coords) {
        updateTime();
        this.m_Coords = coords;
    }

    public Coordinates getDestinationCoordinates() {
        updateTime();
        return m_destinationCoords;
    }
    public void setDestinationCoordinates(Coordinates coords) {
        updateTime();
        this.m_destinationCoords = coords;
        this.m_distance = this.m_Coords.distanceTo(coords);
    }

    public double getDistance(){
        updateTime();
        return m_distance;
    }


    private void updateTime() {
        Instant now = Instant.now();
        Duration elapsedTime = Duration.between(m_lastAccessTime, now);
        double seconds = elapsedTime.toMillis() / 1000.0; // Convert milliseconds to seconds
        double distanceDecrease = m_speed * seconds; // Decrease in distance
        if(this.m_destinationCoords != null) {
            m_distance = this.m_Coords.distanceTo(this.m_destinationCoords);
            m_distance -= distanceDecrease; //!!!!
        }
        m_lastAccessTime = now; // Update last access time
    }



    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("//------------(info)------------//\n");
        sb.append(String.format("//Type:        %-16s  \n", getClass().getSimpleName()));
        sb.append(String.format("//Name:        %-16s  \n", m_Name));
        sb.append(String.format("//Speed:    %-16s  \n", m_speed));
        sb.append(String.format("//DirAngle:    %-16s  \n", m_dirAngle));
        sb.append(String.format("//Coordinates: %-14s   \n", m_Coords.toString()));
        if(m_destinationCoords != null) {
            sb.append(String.format("//DestCoords: %-14s   \n", m_destinationCoords.toString()));
        }
        else{
            sb.append(String.format("//DestCoords: ______\n"));
        }

        sb.append("//------------------------------//");
        return sb.toString();
    }
}
