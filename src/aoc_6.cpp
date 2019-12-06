#include "aoc_6.hpp"

#include <iostream>

using namespace std;

CelestialObject::CelestialObject(const string &name)
{
    _name = name;
    _orbiters = {};
}

string CelestialObject::name() const
{
    return _name;
}

void CelestialObject::set_parent(shared_ptr<CelestialObject> object)
{
    _parent = object;
}

shared_ptr<CelestialObject> CelestialObject::parent()
{
    return _parent;
}

void CelestialObject::add_orbiter(shared_ptr<CelestialObject> object)
{
    _orbiters.push_back(object);
}

shared_ptr<CelestialObject> CelestialObject::find_celestial_body(const string &body_name)
{
    for (auto &orbiter : _orbiters)
    {
        if (orbiter->_name == body_name)
        {
            return orbiter;
        }
        else
        {
            auto finded_body = orbiter->find_celestial_body(body_name);
            if (finded_body)
            {
                return finded_body;
            }
        }
    }
    return {};
}

int CelestialObject::get_distance(const string &body_name)
{
    for (auto &orbiter : _orbiters)
    {
        if (orbiter->_name == body_name)
        {
            return 1;
        }
        else
        {
            int distance = orbiter->get_distance(body_name);
            if (distance != -1)
            {
                return 1 + distance;
            }
        }
    }
    return -1;
}

int CelestialObject::visit(int parent_weight) const
{
    int weight = parent_weight + 1;
    int weight_sum = weight;
    for (auto &orbiter : _orbiters)
    {
        weight_sum += orbiter->visit(weight);
    }
    return weight_sum;
}

void Galaxy::add_orbit(const string &orbitee_name, const string orbiter_name)
{
    shared_ptr<CelestialObject> orbitee;
    shared_ptr<CelestialObject> orbiter;

    // Try to find and already existing orbitee
    bool orbitee_is_orbiter = false;
    for (auto &body : _galaxy)
    {
        if (body->name() == orbitee_name)
        {
            orbitee = body;
            _galaxy.remove(body);
            break;
        }
        else
        {
            if (auto locked_body = body->find_celestial_body(orbitee_name))
            {
                orbitee_is_orbiter = true;
                orbitee = locked_body;
                break;
            }
        }
    }

    // If not founded, create new orbitee
    if (!orbitee)
    {
        orbitee = make_shared<CelestialObject>(orbitee_name);
    }

    // Try to find an orbiter
    for (auto &body : _galaxy)
    {
        if (body->name() == orbiter_name)
        {
            orbiter = body;
            _galaxy.remove(body);
            break;
        }
    }
    // If not founded, create new orbiter
    if (!orbiter)
    {
        orbiter = make_shared<CelestialObject>(orbiter_name);
    }

    orbiter->set_parent(orbitee);
    orbitee->add_orbiter(orbiter);
    if (!orbitee_is_orbiter)
    {
        _galaxy.push_back(orbitee);
    }
    if (orbiter_name == "COM")
    {
        _com = orbiter;
    }
    if (orbitee_name == "COM")
    {
        _com = orbitee;
    }
}

int Galaxy::get_distance(const string &body_name_a, const string &body_name_b)
{
    int distance = -1;
    auto body_a = _com->find_celestial_body(body_name_a);
    if (body_a)
    {
        int counter = 0;
        shared_ptr<CelestialObject> parent = body_a;
        while (parent)
        {
            distance = parent->get_distance(body_name_b);
            if (distance != -1)
            {
                distance += counter;
                break;
            }
            parent = parent->parent();
            counter += 1;
        }
    }
    return distance;
}

int Galaxy::visit() const
{
    int weight_sum = 0;
    for (auto &body : _galaxy)
    {
        weight_sum += body->visit(-1);
    }
    return weight_sum;
}

Galaxy parse_galaxy_file(const string& file_path)
{
    Galaxy galaxy;

    ifstream file_stream(file_path);
    if(!file_stream.fail())
    {
        string names;
        while(!file_stream.eof()) {
            getline(file_stream, names);
            if(!names.empty())
            {
                string::size_type pos = names.find(')');
                string orbitee_name = names.substr(0, pos);
                string orbiter_name = names.substr(pos+1);
                galaxy.add_orbit(orbitee_name, orbiter_name);
            }
        }
    }    

    return galaxy;
}