import java.util.*;
public class StarSystem {
    private String m_Name;
    private Star m_CenterStar;
    private Coordinates m_Coords; //= central star coords
    private List<PlanetSystem> m_PlanetSystems;
    private double m_Area;

    public StarSystem(String name)
    {

        this.m_Name = name;
        this.m_Area = 10000000;
        this.m_PlanetSystems = new ArrayList<>();
    }


    public void setStar(Star star){
        if(this.m_CenterStar == null)
        {
            if(star instanceof PlanetHostingStar) {
                this.m_CenterStar = star;
                this.m_Coords = this.m_CenterStar.getCoordinates();
                //star.setSystem(this.m_Name);
            }
            else {
                System.out.println("ERROR::THE_STAR("+star.getName()+")_IS_NOT_A_PLANET_HOSTING_STAR.");
            }

        }
    }

    //--------------------------(info)--------------------------//
    //Name:             validateCoordinates()                    |
    //Description:      Private function meant to validate       |
    //                  the coordinates of a planetsys relative  |
    //                  to its Central Star. The function is     |
    //                  called before adding a PlanetSystem      |
    //                  to the StarSystem.                       |
    //----------------------------------------------------------//
    private boolean validateCoordinates(PlanetSystem planetSystem){

        Coordinates star_coords = this.m_CenterStar.getCoordinates();
        Coordinates planetsys_coords = planetSystem.getCoordinates();

        double x_min_val = -10000 + star_coords.getX();
        double x_max_val = 10000 + star_coords.getX();

        double y_min_val = -10000 + star_coords.getY();
        double y_max_val = 10000 + star_coords.getY();

        return x_min_val <= planetsys_coords.getX() && x_max_val >= planetsys_coords.getX()
                && y_min_val <= planetsys_coords.getY() && y_max_val >= planetsys_coords.getY();
    }
    public void addPlanetSystem(PlanetSystem planetSystem){

        if(this.m_CenterStar == null)
        {
            System.out.println("ERROR::THIS_STAR_SYSTEM_DOES_NOT_HAVE_A_STAR");
            return;
        }

        if(!validateCoordinates(planetSystem))
        {
            System.out.println("ERROR::PLANET_SYSTEM_COORDINATES_ARE_NOT_POSSIBLE");
            return;
        }

        boolean added = m_PlanetSystems.add(planetSystem);

        if (added) {
            System.out.println("THE_PLANET_SYSTEM("+planetSystem.getName()+")_WAS_ADDED_TO_THE_SYSTEM");
        } else {
            System.out.println("THE_PLANET_SYSTEM("+planetSystem.getName()+")_WAS_ALREADY_IN_THE_SYSTEM");
        }
    }

    public Star getCenteStar(){
        return m_CenterStar;
    }

    public String getName(){
        return m_Name;
    }
    public double getArea() {
        return m_Area;
    }
    public Coordinates getCoordinates() {
        return m_Coords;
    }
    public void setCoordinates(Coordinates coords) {
        this.m_Coords = coords;
    }

    public List<PlanetSystem> getPlanetSystems() { return m_PlanetSystems;}



    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("//------------(info)------------//\n");
        sb.append(String.format("//Type:        %-16s \n", getClass().getSimpleName()));
        String systemInfo = (m_Name.isEmpty()) ? "  Not assigned" : m_Name;
        sb.append(String.format("//Name:      %-18s  \n", systemInfo));
        sb.append(String.format("//CenterStar:      %-18s  \n", m_CenterStar.getName()));

        sb.append("//Planet Systems:\n");
        for (PlanetSystem planetSystem : m_PlanetSystems) {
            sb.append(planetSystem.toString());
        }

        sb.append("//------------------------------//");
        return sb.toString();
    }
}
