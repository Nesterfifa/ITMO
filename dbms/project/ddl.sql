create table UnitHolder
(
	UnitHolderId int primary key
);


create table Lord
(
	UnitHolderId int not null references UnitHolder(UnitHolderId) primary key,
	LordName varchar(30) not null,
	Gender boolean not null,
	BirthDate date not null,
	MeleeSkill int not null constraint correctMelee check (MeleeSkill >= 0),
	RangedSkill int not null constraint correctRanged check (RangedSkill >= 0),
	FatherId int references Lord(UnitHolderId),
	MotherId int references Lord(UnitHolderId)
);

create table Clan
(
	ClanId int primary key,
	ClanLordId int not null references Lord(LordId) deferrable,
	ClanName varchar(30) not null,
	unique (ClanId, ClanLordId)
);

alter table Lord add column ClanId int references Clan(ClanId) deferrable;

create table Attitude
(
	SubjectId int not null references Lord(UnitHolderId),
	ObjectId int not null references Lord(UnitHolderId) constraint differentLords check (ObjectId <> SubjectId),
	AttitudeLevel int not null constraint limitedAttitude check (AttitudeLevel >= -100 and AttitudeLevel <= 100),
	primary key (SubjectId, ObjectId)
);

create table Castle
(
	UnitHolderId int not null references UnitHolder(UnitHolderId),
	LordId int not null references Lord(UnitHolderId),
	CastleName varchar(30) not null,
	WallLevel int not null constraint correctWall check (WallLevel >= 1)
);

create table City
(
	UnitHolderId int not null references UnitHolder(UnitHolderId),
	LordId int not null references Lord(UnitHolderId),
	CityName varchar(30) not null,
	WallLevel int not null constraint correctWall check (WallLevel >= 1),
	VolunteerRanged int not null constraint correctCountRanged check (VolunteerRanged >= 0),
	VolunteerInfantry int not null constraint correctCountInfantry check (VolunteerInfantry >= 0),
	VolunteerCavalry int not null constraint correctCountCavalry check (VolunteerCavalry >= 0)
);

create table Nation
(
	NationId int primary key,
	LeaderId int not null references Lord(UnitHolderId),
	NationName varchar(30) not null
);

create table ClanNation
(
	ClanId int primary key references Clan(ClanId),
	NationId int not null references Nation(NationId)
);

alter table Nation add column NationClanId int references ClanNation(ClanId) deferrable;

create table Unit
(
	UnitId int primary key,
	UnitHolderId int not null references UnitHolder(UnitHolderId),
	NationId int not null references Nation(NationId),
	Count int not null constraint correctCount check (Count >= 1),
	Type char not null constraint correctType check (Type = 'i' or Type = 'r' or Type = 'c'),
	Level int not null constraint correctLevel check (Level >= 1)
);

-- GetAttitude
create unique index on Attitude using btree (SubjectId, ObjectId);

-- GetLord
create index on Lord using hash (LordName);

-- SettlementsNumberByNation
-- ArmyStatistics
create index on Lord using hash (ClanId);

-- SettlementsNumberByNation
-- PoorClans
create index on Castle using hash (UnitHolderId);
create index on City using hash (LordId);

-- Infantry
-- Cavalry
-- Ranged
create index on UnitsWithLord using hash (LordId);

create index on UnitsInCastle using hash (CastleId);
create index on UnitsInCity using hash (CityId);

-- SettlementsNumberByNation
-- PoorClans
create unique index on ClanNation using btree(ClanId, NationId);
create unique index on ClanNation using btree(NationId, ClanId);

-- PostgreSQL automatically creates an index for primary key