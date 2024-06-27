-- transaction level read committed
-- changeClanSovereign
update ClanNation
set NationId = :NewNationId
where NationId = :OldNationId;

-- transaction level read committed
-- makeClanIndependent
delete from ClanNation
where ClanId = :ClanId;

-- transaction level read committed
-- addVolunteers
update City
set VolunteerRanged = VolunteerRanged + 5, 
    VolunteerInfantry = VolunteerInfantry + 3, 
    VolunteerCavalry = VolunteerCavalry + 4
where CityName = :CityName;


-- isolation level repeatable read
create or replace function registerCityLosses(in SquadId int, in LossesCount int)
returns boolean
as 
$registerCityLosses$
begin
    if not exists
    (
        select * from UnitsInCity where UnitsInCity.SquadId = SquadId
    )
    then return false;
    end if;
    
    if LossesCount >=
    (
        select UnitsInCity.Count from UnitsInCity
        where UnitsInCity.SquadId = SquadId
    )
    then
        delete from UnitsInCity where UnitsInCity.SquadId = SquadId;
    else
        update UnitsInCity set Count = Count - LossesCount
        where UnitsInCity.SquadId = SquadId;
    end if;
    return true;
end;
$registerCityLosses$ language plpgsql;

-- isolation level serializable
create or replace function hireVolunteers(in CityId int, in LordId int, in Type char, in HireCount int, in Level int)
returns boolean
as 
$hireVolunteers$
declare
    CityNationId int;
    HirableCount int;
begin
    if not exists
    (
        select * from City where Lord.CityId = CityId
    ) 
    or not exists
    (
        select * from Lord where Lord.LordId = LordId
    )
    then return false;
    end if;
    
    HirableCount = case Type
        when 'i' then
            (select VolunteerInfantry from City where City.CityId = CityId)
        when 'r' then 
            (select VolunteerRanged from City where City.CityId = CityId)
        when 'c' then 
            (select VolunteerCavalry from City where City.CityId = CityId)
        else -1
    end;
    
    if HireCount > HirableCount
    then return false;
    end if;
    
    CityNationId = (
        select NationId from ClanNation where ClanId in
        (
            select ClanId from Lord where Lord.LordId in
            (
                select LordId from City where City.CityId = CityId
            )
        )
    );
    
    if exists (
        select * from UnitsWithLord
        where NationId = CityNationId
            and UnitsWithLord.Level = Level
            and UnitsWithLord.Type = Type
            and UnitsWithLord.LordId = LordId
    )
    then
        update UnitsWithLord set Count = Count + HireCount
        where NationId = CityNationId
            and UnitsWithLord.Level = Level
            and UnitsWithLord.Type = Type
            and UnitsWithLord.LordId = LordId;
    else
        insert into UnitsWithLord (NationId, LordId, Count, Type, Level)
        values (CityNationId, LordId, HireCount, Type, Level);
    end if;
    
    update City set VolunteerInfantry = VolunteerInfantry - HireCount
    where City.CityId = CityId and Type = 'i';
    update City set VolunteerRanged = VolunteerRanged - HireCount
    where City.CityId = CityId and Type = 'r';
    update City set VolunteerCavalry = VolunteerCavalry - HireCount
    where City.CityId = CityId and Type = 'c';
    
    return true;
end;
$hireVolunteers$ language plpgsql;

create or replace function processCheckLeaderNation() returns trigger
as $checkLeaderNation$
begin
    if exists
    (
        select * from Nation
        where exists
        (
            select * from Lord
            where Lord.LordId = Nations.LeaderId
            and Lord.ClanId not in
            (
                select ClanId from ClanNation
                where ClanNation.NationId = Nation.NationId
            )
        )
    )
    then
        raise exception 'Leader is from another nation.';
    end if;
    return null;
end;
$checkLeaderNation$ language plpgsql;

create or replace function processCheckParentGender() returns trigger
as $checkParentGender$
begin
    if exists
    (
        select * from Lord
        where FatherId is not null
            and FatherId not in
            (
                select LordId from Lord
                where Gender = 0
            )
            or MotherId is not null
            and MotherId not in
            (
                select LordId from Lord
                where Gender = 1
            )
    )
    then
        raise exception 'Wrong parent gender.';
    end if;
    return null;
end;
$checkParentGender$ language plpgsql;

create or replace function checkWitnessLordId()
returns trigger
as $checkWitnessLordId$
begin
    if exists
    (
        select * from Lord
        where exists
        (
            select * from Clan
            where Clan.LordId = Lord.LordId
                and Lord.ClanId <> Clan.ClanId
        )
    )
    then 
        update Clan set LordId = 
            (
                select LordId from Lords
                where Lords.ClanId = Clan.ClanId
                limit 1
            );
    end if;
    return null;
end;
$checkWitnessLordId$ language plpgsql;

create or replace function checkWitnessClanId()
returns trigger
as $checkWitnessClanId$
begin
    if exists
    (
        select * from Nation
        where exists
        (
            select * from ClanNation
            where ClanNation.ClanId = Nation.ClanId
                and Clan.NationId <> Nation.NationId
        )
    )
    then 
        update Nation set ClanId = 
            (
                select ClanId from ClanNation
                where Nation.NationId = ClanNation.NationId
                limit 1
            );
    end if;
    return null;
end;
$checkWitnessClanId$ language plpgsql;

create or replace trigger checkLeaderNationNation
after update or insert
on Nation
for each row
execute procedure processCheckLeaderNation();

create or replace trigger checkLeaderNationLord
after update
on Lord
for each row
execute procedure processCheckLeaderNation();

create or replace trigger checkLeaderNationClan
after update or insert
on Clan
for each row
execute procedure processCheckLeaderNation();

create or replace trigger checkParentGender
after update or insert
on Lord
for each row
execute procedure processCheckParentGender();

create or replace trigger checkWitnessLordLord
after update
on Lord
for each row
execute procedure checkWitnessLordId();

create or replace trigger checkWitnessLordClan
after update or insert
on Clan
for each row
execute procedure checkWitnessLordId();

create or replace trigger checkWitnessClanNation
after update or insert
on Nation
for each row
execute procedure checkWitnessClanId();

create or replace trigger checkWitnessClanClanNation
after update or insert
on ClanNation
for each row
execute procedure checkWitnessClanId();