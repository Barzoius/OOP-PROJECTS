public class Satellite {
    private String m_Name;
    private double m_Diameter; // in km
    private double m_GravitationalPull; // in newtons
    private Coordinates m_Coords;

    public Satellite(String name, double diameter, double grav, Coordinates coords)
    {
        this.m_Name = name;
        this.m_Diameter = diameter;
        this.m_GravitationalPull = grav;
        this.m_Coords = coords;
    }

    public String getName() {
        return m_Name;
    }

    public void setName(String name) {
        this.m_Name = name;
    }

    public double getDiameter() {
        return m_Diameter;
    }

    public void setDiameter(double diameter) {
        this.m_Diameter = diameter;
    }

    public double getGravitationalPull() {
        return m_GravitationalPull;
    }

    public void setGravitationalPull(double gravPull) {
        this.m_GravitationalPull = gravPull;
    }

    public Coordinates getCoordinates() {
        return m_Coords;
    }

    public void setCoordinates(Coordinates coords) {
        this.m_Coords = coords;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("//------------(info)------------//\n");
        sb.append(String.format("//Type:        %-16s  \n", getClass().getSimpleName()));
        sb.append(String.format("//Name:        %-16s  \n", m_Name));
        sb.append(String.format("//Diameter:    %-16s  \n", m_Diameter));
        sb.append(String.format("//GravPull:    %-16s  \n", m_GravitationalPull));
        //sb.append(String.format("//Coordinates: %-14s   |\n", m_Coords.toString()));
        sb.append("//------------------------------//");
        return sb.toString();
    }
}
