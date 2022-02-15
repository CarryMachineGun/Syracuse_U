function initialise_model_weights(layer_dims)
    for l = 2:layer_dims
        println(l);
    end
end

function main()
    initialise_model_weights(6)
end


main()