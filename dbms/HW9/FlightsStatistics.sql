create or replace function FlightsStatistics(in UserId int, in Pass varchar(255))
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
    if not has_user(FlightsStatistics.UserId, FlightsStatistics.Pass) then
        return query
            select;
    else
        return query
            select
                flights.flight_id as flight_id,
                is_booking_available(flights.flight_id) as booking_available,
                is_purchase_available(flights.flight_id) as purchase_available,
                (select count(*) as cnt from FreeSeats(flights.flight_id)) as free,
                count_booked(flights.flight_id) as booked,
                count_purchased(flights.flight_id) as purchased
            from
                flights;
    end if;
end;
$$