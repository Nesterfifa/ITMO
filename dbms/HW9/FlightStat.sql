create or replace function FlightStat
    (
        in UserId int,
        in Pass varchar(255), 
        in FlightId int
    )
returns table 
    (
        flight_id int,
        booking_available boolean,
        purchase_available boolean,
        free int,
        booked int,
        purchased int
    )
language plpgsql
as
$$
begin
    if not has_flight(BuyFree.FlightId) then
        return query
            select;
    end if;
    return query
        select
            flight_id,
            booking_available,
            purchase_available,
            free,
            booked,
            purchased
        from
            FlightsStatistics(FlightStat.UserId, FlightStat.Pass) as FS
        where
            FS.flight_id = FlightStat.FlightId;
end;
$$