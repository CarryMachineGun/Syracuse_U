
function main()
    arr = [2,3,5,21,233,2,5,12,3,5]
    mergeSort(arr);

    println(arr);
end

function mergeSort(arr, l = 1, r = length(arr))
    if l >= r 
        return
    end
    q = (l + r) ÷ 2
    # println(q)
    mergeSort(arr, l, q)
    mergeSort(arr, q+1, r)
    merge(arr, l, q, r)
end

function merge(arr, l, q, r)
    guard = typemax(eltype(arr))
    L = arr[l : q]
    R = arr[(q+1) : r]

    push!(L, guard)
    push!(R, guard)

    i = 1
    j = 1

    for k in l:r
      if L[i] <= R[j]
          arr[k] = L[i]
          i += 1
      else
          arr[k] = R[j]
          j += 1
      end
    end
end


main()