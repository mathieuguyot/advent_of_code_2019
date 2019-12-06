#ifndef DEF_AOC_6_HPP
#define DEF_AOC_6_HPP

#include <string>
#include <list>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>

class CelestialObject
{
public:
    CelestialObject(const std::string& name);
    std::string name() const;
    void set_parent(std::shared_ptr<CelestialObject> object);
    std::shared_ptr<CelestialObject> parent();
    void add_orbiter(std::shared_ptr<CelestialObject> object);
    std::shared_ptr<CelestialObject> find_celestial_body(const std::string& body_name);
    int get_distance(const std::string& body_name);
    int visit(int parent_weight) const;

protected:
    std::shared_ptr<CelestialObject> _parent;
    std::string _name;
    std::list<std::shared_ptr<CelestialObject>> _orbiters;
};

class Galaxy
{
public:
    void add_orbit(const std::string& orbitee_name, const std::string orbiter_name);
    int get_distance(const std::string& body_name_a, const std::string& body_name_b);
    int visit() const;

protected:
    std::list<std::shared_ptr<CelestialObject>> _galaxy;
    std::shared_ptr<CelestialObject> _com;
};

Galaxy parse_galaxy_file(const std::string& file_path);

#endif