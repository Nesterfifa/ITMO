create view Infantry as
select LordId, SquadId as InfantryId, Count as InfantryCount, Level as InfantryLevel
from Lord natural join UnitsWithLord
where Type = 'i';

create view Ranged as
select LordId, SquadId as RangedId, Count as RangedCount, Level as RangedLevel
from Lord natural join UnitsWithLord
where Type = 'r';

create view Cavalry as
select LordId, SquadId as CavalryId, Count as CavalryCount, Level as CavalryLevel
from Lord natural join UnitsWithLord
where Type = 'c';

-- LordByName
select LordId, LordName, Age, Gender, BirthDate, MeleeSkill, RangedSkill
from Lord
where LordName = :LordName;

-- GetAttitude
select SubjectId, ObjectId, AttitudeLevel
from Attitude
where SubjectId = :SubjectId and ObjectId = :ObjectId;

-- SettlementsNumberByNation
select 
    NationId, 
    NationName,
    NumberOfCastles,
    NumberOfCities
from
    (
        select NationId, NationName, count(CastleId) as NumberOfCastles
        from Nation 
            natural join ClanNation 
            natural join Lord
            natural join Castle
        group by NationId
    ) Castles
    natural join (
        select NationId, NationName, count(CityId) as NumberOfCities
        from Nation 
            natural join ClanNation 
            natural join Lord
            natural join City
        group by NationId
    ) Cities
where NationName = :NationName;

-- ArmyStatistics
select
    NationId,
    coalesce(sum(InfantryCount), 0) as Infantry,
    coalesce(sum(RangedCount), 0) as Ranged,
    coalesce(sum(CavalryCount), 0) as Cavalry,
    coalesce(sum(InfantryCount), 0) + coalesce(sum(RangedCount), 0) + coalesce(sum(CavalryCount), 0) as Army
from
    Lord
    natural join ClanNation
    left join Infantry on Infantry.LordId = Lord.LordId
    left join Ranged on Ranged.LordId = Lord.LordId
    left join Cavalry on Cavalry.LordId = Lord.LordId
group by NationId
order by NationId;

-- Ancestors
with recursive Ancestor(LordId, AId) as
(
    (
        select LordId, MotherId as AId from Lord 
        where MotherId is not null
        union
        select LordId, FatherId as AId from Lord
        where FatherId is not null
    )
    union
    select L.LordId, A.AId from Ancestor A
        inner join Lord L 
            on L.FatherId = A.LordId or L.MotherId = A.LordId
    where A.Aid is not null
)
select * from Ancestor where LordId = 4;

-- PoorClans
select ClanId, ClanName from Clan
where not exists
    (
        select * from Lord
        where exists
            (
                select * from Castle
                where Castle.LordId = Lord.LordId
            )
            or exists
            (
                select * from City
                where City.LordId = Lord.LordId
            )
    );

-- WeakClans
select ClanId, ClanName from Clan
where not exists
    (
        select * from Lord
        where exists
            (
                select * from UnitsWithLord
                where 
                    UnitsWithLord.LordId = Lord.LordId 
                    and Level > 2
            )
    );
