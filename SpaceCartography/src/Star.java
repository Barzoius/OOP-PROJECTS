public class Star {

    private String m_Name;
    private double m_Diameter; // in km
    private double m_GravitationalPull; // in newtons

    private String m_StarSystemName;

    Coordinates m_Coords;

    Star()
    {

    }

    Star(String name, double diameter, double gravPull, Coordinates coords)
    {
        this.m_Name = name;
        this.m_Diameter = diameter;
        this.m_GravitationalPull = gravPull;
        this.m_Coords = coords;
    }

    public static Star createStar(String name, double diameter, double gravPull, Coordinates coords) {
        if (diameter > 100000) {
            return new PlanetHostingStar(name, diameter, gravPull, coords);
        } else if (diameter < 10000) {
            return new DwarfStar(name, diameter, gravPull, coords);
        } else {
            return new Star(name, diameter, gravPull, coords);
        }
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
        sb.append(String.format("//Coordinates: %-14s   \n", m_Coords.toString()));
        sb.append("//------------------------------//");
        return sb.toString();
    }
}
