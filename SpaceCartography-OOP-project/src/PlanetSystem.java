import java.util.*;
public class PlanetSystem {

    String m_Name;
    Planet m_CenterPlanet;
    Coordinates m_Coords;
    Set<Satellite> m_Satellites;

    public PlanetSystem(String name)
    {
        this.m_Name = name;
        this.m_Satellites = new HashSet<>();
    }

    public Planet getCenterPlanet() {return m_CenterPlanet;}
    public void setName(String name) { this.m_Name = name;}
    public String getName() { return m_Name;}

    public Coordinates getCoordinates() {
        return m_Coords;
    }

    public void setCoordinates(Coordinates coords) {
        this.m_Coords = coords;
    }



    //--------------------------(info)--------------------------//
    //Name:             setPlanet()                              |
    //Description:      Public function to set a PlanetSystem's  |
    //                  m_CenterPlanet. Once added it sets the   |
    //                  coordinates of the system to the ones of |
    //                  its center planet. After it calls        |
    //                  setSystem() in order to set the planet's |
    //                  m_PlanetSystemName variable.             |
    //----------------------------------------------------------//
    public void setPlanet(Planet planet){
        if(this.m_CenterPlanet == null)
        {
            this.m_CenterPlanet = planet;
            this.m_Coords = this.m_CenterPlanet.getCoordinates();
            planet.setSystem(this.m_Name);
        }
    }

    //--------------------------(info)--------------------------//
    //Name:             validateCoordinates()                    |
    //Description:      Private function meant to validate       |
    //                  the coordinates of a satellite relative  |
    //                  to its Central Planet. The function is   |
    //                  called before adding a satellite to the  |
    //                  PlanetSystem.                            |
    //----------------------------------------------------------//
    private boolean validateCoordinates(Satellite satellite){

        Coordinates planet_coords = this.m_CenterPlanet.getCoordinates();
        Coordinates satellite_coords = satellite.getCoordinates();

        double x_min_val = -1000 + planet_coords.getX();
        double x_max_val = 1000 + planet_coords.getX();

        double y_min_val = -1000 + planet_coords.getY();
        double y_max_val = 1000 + planet_coords.getY();

        return x_min_val <= satellite_coords.getX() && x_max_val >= satellite_coords.getX()
                && y_min_val <= satellite_coords.getY() && y_max_val >= satellite_coords.getY();
    }
    public void addSatellite(Satellite satellite){

        if(this.m_CenterPlanet == null)
        {
            System.out.println("ERROR::THIS_PLANET_SYSTEM_DOES_NOT_HAVE_A_PLANET");
            return;
        }

        if(!validateCoordinates(satellite))
        {
            System.out.println("ERROR::SATELLITE_COORDINATES_ARE_NOT_POSSIBLE");
            return;
        }

        boolean added = m_Satellites.add(satellite);

        if (added) {
            System.out.println("THE_SATELLITE("+satellite.getName()+")_WAS_ADDED_TO_THE_SYSTEM");
        } else {
            System.out.println("THE_SATELLITE("+satellite.getName()+")_WAS_ALREADY_IN_THE_SYSTEM");
        }
    }

    public Set<Satellite> getSatellites()
    {
        return m_Satellites;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("//------------(info)------------//\n");
        sb.append(String.format("//Type:        %-16s  \n", getClass().getSimpleName()));
        String systemInfo = (m_Name.isEmpty()) ? "  Not assigned" : m_Name;
        sb.append(String.format("//Name:      %-18s  \n", systemInfo));




        sb.append("//------------------------------//");
        return sb.toString();
    }
}


